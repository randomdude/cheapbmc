using System;
using System.Runtime.InteropServices;

namespace cheapbmc_net
{
    public static class interop_cheapbmc
    {
        public delegate void onErrorDlg(string msg);
        public delegate void onErrorCurlDlg(string msg, UInt32 errorCode);

        [DllImport("cheapbmc.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, ExactSpelling = true)]
        public static extern int getPowerState(string IP, string CACert, string clientCert, string clientKey);

        [DllImport("cheapbmc.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, ExactSpelling = true)]
        public static extern int powerButtonPress(string IP, string CACert, string clientCert, string clientKey, bool isLong);

        [DllImport("cheapbmc.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi, ExactSpelling = true)]
        public static extern int setErrorCallback(onErrorDlg err, onErrorCurlDlg errCurl);
    }

}
