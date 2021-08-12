using System;

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
            int res = interop_cheapbmc.getPowerState(_ip, _caCert, _clientCert, _clientKey);
            if (res == 0)
                return false;
            else
                return true;
        }
    }
}