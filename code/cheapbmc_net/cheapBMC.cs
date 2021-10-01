using System;
using System.IO;
using System.Text;
using SeasideResearch.LibCurlNet;

namespace cheapbmc_net
{
    public class cheapBMC
    {
        private readonly string _ip;
        private readonly string _caCert;
        private readonly string _clientCert;
        private readonly string _clientKey;

        // Gotta keep references to these around so they don't get GC'd.
        // ReSharper disable PrivateFieldCanBeConvertedToLocalVariable
        private static interop_cheapbmc.onErrorDlg onErrorDlg;
        private static interop_cheapbmc.onErrorCurlDlg onErrorCurlDlg;
        // ReSharper restore PrivateFieldCanBeConvertedToLocalVariable

        private static Object initDlgsLock = new Object();

        public cheapBMC(string IP, string CACert, string clientCert, string clientKey)
        {
            _ip = IP;
            _caCert = CACert;
            _clientCert = clientCert;
            _clientKey = clientKey;

            if (onErrorDlg == null)
            {
                lock (initDlgsLock)
                {
                    if (onErrorDlg == null)
                    {
                        Curl.GlobalInit((int) CURLinitFlag.CURL_GLOBAL_ALL);

                        onErrorDlg = onError;
                        onErrorCurlDlg = onErrorCurl;

                        interop_cheapbmc.setErrorCallback(onErrorDlg, onErrorCurlDlg);
                    }
                }
            }
        }

        private static void onError(string msg)
        {
            throw new Exception(msg);
        }

        private static void onErrorCurl(string msg, UInt32 errorCode)
        {
            throw new CurlException(msg, errorCode);
        }

        public bool getPowerState()
        {
            StringBuilder htmlText = new StringBuilder();

            using (var stream = new StringWriter(htmlText))
            {
                using (var easy = new Easy())
                {
                    easy.SetOpt(CURLoption.CURLOPT_URL, $"https://{_ip}/getPowerStatus");

                    easy.SetOpt(CURLoption.CURLOPT_WRITEFUNCTION, new Easy.WriteFunction((data, size, nemb, user) =>
                    {
                        int length = size * nemb;
                        stream.Write(Encoding.ASCII.GetChars(data, 0, length));
                        return length;
                    }));

                    CURLcode fetchRes = easy.Perform();
                    if (fetchRes != CURLcode.CURLE_OK)
                        throw new CurlException("Failed to get power state", (uint)fetchRes);

                    string resultText = htmlText.ToString().Trim();
                    if (resultText == "0")
                        return false;
                    if (resultText == "1")
                        return true;

                    throw new Exception($"Unrecognised result for getPowerStatus: '{resultText}'");
                }
            }

            //int res = interop_cheapbmc.getPowerState(_ip, _caCert, _clientCert, _clientKey);
        }

        public void doPowerButtonPush(bool isLongPush)
        {
            interop_cheapbmc.powerButtonPress(_ip, _caCert, _clientCert, _clientKey, isLongPush);
        }

    }
}