// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <exception>
#include <string>
#include <iomanip>
#include <sstream>
#include <memory>

#include <openssl/ssl.h>
#include <curl/curl.h>
#include "public.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

class memoryAndSize
{
public:
	memoryAndSize()
	{
		size = 0;
		memory = (char*)malloc(1);
	}

	void append(size_t sizeOfNewData, char* data)
	{
		char *ptr = (char*)realloc(memory, size + sizeOfNewData + 1);
		if (!ptr) {
			anyError = new std::exception("out of memory");
		}

		memory = ptr;
		memcpy(&(memory[size]), data, sizeOfNewData);
		size += sizeOfNewData;
		memory[size] = '\0';
	}

	void throwIfNeeded()
	{
		if (anyError != NULL)
			throw *anyError;
	}

	~memoryAndSize()
	{
		if (anyError != NULL)
			delete anyError;
		free(memory);
		memory = NULL;
		size = 0;
	}

	char *memory;
	size_t size;

	std::exception* anyError;

};

static size_t writefunction(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	memoryAndSize *mem = (memoryAndSize*)userp;

	mem->append(realsize, (char*)contents);

	return realsize;
}

curlException::curlException(char* funcName, CURLcode errorCode, char* extra)
{
	std::stringstream ss;
	if (extra != NULL)
		ss << extra;
	ss << "' failed " << funcName << " : " << curl_easy_strerror(errorCode);
	this->msg = (char*)malloc(ss.str().size() + 1);
	memcpy(this->msg, ss.str().c_str(), ss.str().size());
	this->msg[ss.str().size()] = '\0';
	this->errorCode = errorCode;
}

curlException::~curlException()
{
}

char const* curlException::what() const
{
	return msg;
}


static CURLcode sslctx_function(CURL *curl, void *sslctx, void *parm)
{
	char* caCert = (char*)parm;

	if (caCert != NULL)
	{
		BIO *cbio = BIO_new_mem_buf(caCert, strlen(caCert));
		if (!cbio)
			return CURLE_ABORTED_BY_CALLBACK;

		X509_STORE *cts = SSL_CTX_get_cert_store((SSL_CTX*)sslctx);
		int i;
		STACK_OF(X509_INFO) *inf;
		(void)curl;
		(void)parm;

		if (!cts) {
			BIO_free(cbio);
			return CURLE_ABORTED_BY_CALLBACK;
		}

		inf = PEM_X509_INFO_read_bio(cbio, NULL, NULL, NULL);

		if (!inf)
		{
			BIO_free(cbio);
			return CURLE_ABORTED_BY_CALLBACK;
		}

		for (i = 0; i < sk_X509_INFO_num(inf); i++) 
		{
			X509_INFO *itmp = sk_X509_INFO_value(inf, i);
			if (itmp->x509) 
			{
				X509_STORE_add_cert(cts, itmp->x509);
			}
			if (itmp->crl) 
			{
				X509_STORE_add_crl(cts, itmp->crl);
			}
		}

		sk_X509_INFO_pop_free(inf, X509_INFO_free);
		BIO_free(cbio);
	}
	return CURLE_OK;
}

class curlEasy
{
public:
	curlEasy()
	{
		curl = curl_easy_init();
		if (!curl)
			throw std::runtime_error("Failed curl_easy_init");

//		curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);

		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunction);
	}

	memoryAndSize* perform(char* url = NULL)
	{
		if (url != NULL)
			curl_easy_setopt(curl, CURLOPT_URL, url);

		CURLcode rv = curl_easy_perform(curl);
		if (rv != CURLE_OK)
			throw curlException((char*)"curl_easy_perform", rv);
		response.throwIfNeeded();

		return &response;
	}

	void setCACert(char* cacert)
	{
		if (cacert != NULL)
		{
			curl_easy_setopt(curl, CURLOPT_CAINFO, NULL);
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_FUNCTION, sslctx_function);
			curl_easy_setopt(curl, CURLOPT_SSL_CTX_DATA, cacert);
		}
	}

	void setClientCert(char* certText)
	{
		if (certText != NULL)
		{
			sslCertBlob.len = strlen(certText);
			sslCertBlob.data = certText;
			curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, "PEM");
			curl_easy_setopt(curl, CURLOPT_SSLCERT_BLOB, &sslCertBlob);
		}
	}

	void setClientKey(char* keyText)
	{
		if (keyText != NULL)
		{
			sslKeyBlob.len = strlen(keyText);
			sslKeyBlob.data = keyText;
			curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, "PEM");
			curl_easy_setopt(curl, CURLOPT_SSLKEY_BLOB, &sslKeyBlob);
		}
	}

	~curlEasy()
	{
		curl_easy_cleanup(curl);
		curl = NULL;
	}
	CURL *curl;

private:
	curl_blob sslKeyBlob;
	curl_blob sslCertBlob;

	memoryAndSize response;
};

errorCallback_curl onError_curl = NULL;
errorCallback onError = NULL;
void __cdecl setErrorCallback(errorCallback newCB, errorCallback_curl newCB_curl )
{
	onError = newCB;
	onError_curl = newCB_curl;
}

unsigned long _getPowerState(char* IP, char* cacert, char* clientCert, char* clientKey)
{
	curl_global_init(CURL_GLOBAL_ALL);
	{
		curlEasy crl;

		crl.setCACert(cacert);
		crl.setClientCert(clientCert);
		crl.setClientKey(clientKey);

		std::stringstream urlStr;
		urlStr << "https://" << IP << ":443/getTargetStatus";

		memoryAndSize* resp = crl.perform((char*)urlStr.str().c_str());
		
		if (_strnicmp(resp->memory, "ON", resp->size) == 0)
		{
			return true;
		}
		else if (_strnicmp(resp->memory, "OFF", resp->size) == 0)
		{
			return false;
		}
		else
		{
			std::stringstream ss;
			ss << "Unrecognised response text: " << resp->memory;
			throw std::runtime_error(ss.str());
		}
	}
	curl_global_cleanup();
}

unsigned long getPowerState(char* IP, char* cacert, char* clientCert, char* clientKey)
{
	try
	{
		return _getPowerState(IP, cacert, clientCert, clientKey);
	}
	catch (curlException &e)
	{
		if (onError_curl != NULL)
		{
			onError_curl((char*)e.what(), e.errorCode);
			return 0;
		}
		else
		{
			throw;
		}
	}
	catch (std::exception &e)
	{
		if (onError != NULL)
		{
			onError((char*)e.what());
			return 0;
		}
		else
		{
			throw;
		}
	}
}

void _doReset(char* IP, char* cacert, char* clientCert, char* clientKey)
{
	curl_global_init(CURL_GLOBAL_ALL);
	{
		curlEasy crl;

		crl.setCACert(cacert);
		crl.setClientCert(clientCert);
		crl.setClientKey(clientKey);

		std::stringstream urlStr;
		urlStr << "https://" << IP << ":443/doReset";

		curl_easy_setopt(crl.curl, CURLOPT_POST, true);

		memoryAndSize* resp = crl.perform((char*)urlStr.str().c_str());

		if (_strnicmp(resp->memory, "OK", resp->size) == 0)
			return;

		std::stringstream ss;
		ss << "Unrecognised response text: " << resp->memory;
		throw std::runtime_error(ss.str());
	}
	curl_global_cleanup();
}

void doReset(char* IP, char* cacert, char* clientCert, char* clientKey)
{
	try
	{
		_doReset(IP, cacert, clientCert, clientKey);
	}
	catch (curlException &e)
	{
		if (onError_curl != NULL)
		{
			onError_curl((char*)e.what(), e.errorCode);
			return;
		}
		else
		{
			throw;
		}
	}
	catch (std::exception &e)
	{
		if (onError != NULL)
		{
			onError((char*)e.what());
			return;
		}
		else
		{
			throw;
		}
	}
}
