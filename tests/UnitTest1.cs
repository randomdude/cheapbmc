using System;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Security;
using System.Security.Cryptography.X509Certificates;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace tests
{
    [TestClass]
    public class testHTTPS
    {
        [TestMethod]
        public void testConnection()
        {
            HttpWebRequest req = WebRequest.CreateHttp("https://192.168.90.104");

            ServicePointManager.Expect100Continue = false;
            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls11 | 
                SecurityProtocolType.Tls12 | SecurityProtocolType.Tls | SecurityProtocolType.Ssl3;

            var clientcert = new X509Certificate2("C:\\code\\ipmihw\\cheapbmc\\keys\\client\\access.pfx");
            req.ClientCertificates.Clear();
            req.ClientCertificates.Add(clientcert);
            Assert.IsTrue(clientcert.HasPrivateKey);
            req.ServerCertificateValidationCallback += verifyCert_legit;
            using (var resp = req.GetResponse())
            {
            }
        }


        [TestMethod]
        public void testRejectionWithoutKey()
        {
            HttpWebRequest req = WebRequest.CreateHttp("https://192.168.90.104");

            ServicePointManager.Expect100Continue = false;
            ServicePointManager.SecurityProtocol = SecurityProtocolType.Tls11 |
                SecurityProtocolType.Tls12 | SecurityProtocolType.Tls | SecurityProtocolType.Ssl3;

            req.ServerCertificateValidationCallback += verifyCert_legit;
            try
            {
                using (var resp = req.GetResponse())
                {
                }
            }
            catch(System.Net.WebException e)
            {
                Assert.IsTrue(e.Message.Contains("Authentication failed"));
                return;
            }

            Assert.Fail("Connection without client key succeded but should fail");
        }

        private bool verifyCert_legit(object sender, X509Certificate certificate, X509Chain chain, SslPolicyErrors sslPolicyErrors)
        {
            return true;

            if (chain.ChainStatus.Any(statusFlags => statusFlags.Status != X509ChainStatusFlags.UntrustedRoot))
                return false;

            var legitcert = new X509Certificate("C:\\code\\ipmihw\\cheapbmc\\keys\\ca\\ca.crt");

            var caEffectiveDate = DateTime.Parse(legitcert.GetEffectiveDateString());
            var caExpirationDate = DateTime.Parse(legitcert.GetExpirationDateString());
            var now = DateTime.UtcNow;
            if (now <= caEffectiveDate || now > caExpirationDate)
                return false;

            return chain.ChainElements.Cast<X509ChainElement>()
                                      .Select(element => element.Certificate)
                                      .Where(chainCertificate => chainCertificate.Subject == legitcert.Subject)
                                      .Where(chainCertificate => chainCertificate.GetRawCertData().SequenceEqual(legitcert.GetRawCertData()))
                                      .Any();
        }
    }
}
