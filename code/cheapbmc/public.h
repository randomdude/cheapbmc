#ifdef CHEAPBMC_EXPORTS
#define spec __declspec(dllexport)
#else
#define spec __declspec(dllimport)
#endif

extern "C"
{
	typedef void(*errorCallback)(char* message);
	typedef void(*errorCallback_curl)(char* message, CURLcode errorCode);

	spec unsigned long __cdecl getPowerState(char* IP, char* cacert, char* clientCert, char* clientKey);
	spec void __cdecl doReset(char* IP, char* cacert, char* clientCert, char* clientKey);

	spec void __cdecl setErrorCallback(errorCallback newCB, errorCallback_curl newCB_Curl);
}

class curlException : public std::exception
{
public:
	curlException(char* funcName, CURLcode errorCode, char* extra = NULL);

	~curlException();
	char const* what() const override;

	CURLcode errorCode;
private:
	char* msg;
};


