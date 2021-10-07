using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

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

                        // If this dll is present in the current directory, great, we're a 32/64bit build and
                        // the modules are available and it will Just Work.
                        // If not, however, then we should look in the x86 or x64 directory in order to find
                        // the modules we require.
                        if (File.Exists("cheapbmc.dll") == false)
                        {
                            if (IntPtr.Size == 4)
                            {
                                LoadLibraryThrowing("x86/libcrypto-1_1.dll");
                                LoadLibraryThrowing("x86/libssl-1_1.dll");
#if DEBUG
                                LoadLibrary("x86/zlibd1.dll");
                                LoadLibraryThrowing("x86/libcurl-d.dll");
#else
                                LoadLibraryThrowing("x86/zlib1.dll");
                             LoadLibraryThrowing("x86/libcurl.dll");
#endif
                                LoadLibraryThrowing("x86/cheapbmc.dll");
                            }
                            else
                            {
                                LoadLibraryThrowing("x64/libcrypto-1_1-x64.dll");
                                LoadLibraryThrowing("x64/libssl-1_1-x64.dll");
#if DEBUG
                                LoadLibraryThrowing("x64/zlibd1.dll");
                                LoadLibraryThrowing("x64/libcurl-d.dll");
#else
                                LoadLibraryThrowing("x64/zlib1.dll");
                                LoadLibraryThrowing("x64/libcurl.dll");
#endif
                                LoadLibraryThrowing("x64/cheapbmc.dll");
                            }
                        }

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
            return res != 0;
        }

        public void doPowerButtonPush(bool isLongPush)
        {
            interop_cheapbmc.doPowerButtonPress(_ip, _caCert, _clientCert, _clientKey, isLongPush);
        }

        private static void LoadLibraryThrowing(string filename)
        {
            IntPtr res = LoadLibrary(filename);
            if (res == IntPtr.Zero)
                throw new Win32Exception(Marshal.GetLastWin32Error());
        }

        [DllImport("kernel32", SetLastError = true, CharSet = CharSet.Ansi)]
        private static extern IntPtr LoadLibrary([MarshalAs(UnmanagedType.LPStr)]string lpFileName);
    }
}