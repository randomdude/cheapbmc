using System.IO;
using cheapbmc_net;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace tests
{
    [TestClass]
    public class testHTTPS
    {
        private string testBMCIP = "192.168.90.20";

        [TestMethod]
        [DeploymentItem("cheapbmc.dll")]
        [DeploymentItem("libcrypto-1_1.dll")]
        [DeploymentItem("libssl-1_1.dll")]
        [DeploymentItem("libcurl-d.dll")]
        [DeploymentItem("zlibd1.dll")]
        public void testConnection()
        {
            cheapBMC uut = new cheapBMC(
                testBMCIP,
                File.ReadAllText("C:\\code\\cheapbmc\\keys\\ca\\ca.crt"),
                File.ReadAllText("C:\\code\\cheapbmc\\keys\\client\\access.crt"),
                File.ReadAllText("C:\\code\\cheapbmc\\keys\\client\\access.key")
            );

            uut.getPowerState();
        }

        [TestMethod]
        [DeploymentItem("cheapbmc.dll")]
        [DeploymentItem("libcrypto-1_1.dll")]
        [DeploymentItem("libssl-1_1.dll")]
        [DeploymentItem("libcurl-d.dll")]
        [DeploymentItem("zlibd1.dll")]
        public void testRejectionWithoutKey()
        {
            cheapBMC uut = new cheapBMC(
                testBMCIP,
                File.ReadAllText("C:\\code\\cheapbmc\\keys\\ca\\ca.crt"), 
                null, 
                null
            );

            try
            {
                uut.getPowerState();
            }
            catch (CurlException e)
            {
                Assert.AreEqual(curlErrorCode.CURLE_SSL_CONNECT_ERROR, e.errorCode);
                return;
            }

            Assert.Fail("Exception was not thrown");
        }

        [TestMethod]
        [DeploymentItem("cheapbmc.dll")]
        [DeploymentItem("libcrypto-1_1.dll")]
        [DeploymentItem("libssl-1_1.dll")]
        [DeploymentItem("libcurl-d.dll")]
        [DeploymentItem("zlibd1.dll")]
        public void testRejectionWithoutCACert()
        {
            cheapBMC uut = new cheapBMC(
                testBMCIP,
                null,
                File.ReadAllText("C:\\code\\cheapbmc\\keys\\client\\access.crt"),
                File.ReadAllText("C:\\code\\cheapbmc\\keys\\client\\access.key")
            );

            try
            {
                uut.getPowerState();
            }
            catch (CurlException e)
            {
                Assert.AreEqual(curlErrorCode.CURLE_PEER_FAILED_VERIFICATION, e.errorCode);
                return;
            }

            Assert.Fail("Exception was not thrown");
        }
    }
}
