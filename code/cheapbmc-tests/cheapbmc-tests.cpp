#include <iostream>

#include <gtest/gtest.h>

#include "curl/curl.h"
#include "../../cheapbmc/public.h"

char* IP = (char*)"192.168.90.20";

char* cacrt = (char*)"-----BEGIN CERTIFICATE-----\n\
MIIEdDCCA1ygAwIBAgIUaZQpYmEbkAMKXcodM6DqVKWoALowDQYJKoZIhvcNAQEL\n\
BQAwfDELMAkGA1UEBhMCU0cxETAPBgNVBAgMCEFsaXpMYW5kMREwDwYDVQQHDAhB\n\
bGl6TGFuZDENMAsGA1UECgwEQWxpejENMAsGA1UECwwEQWxpejEpMCcGA1UEAwwg\n\
bWFuYWdlbWVudC5ob21lLmdhbWVzZmFpcnkuY28udWswHhcNMjEwNzEwMTUwMjE5\n\
WhcNMjEwODA5MTUwMjE5WjB8MQswCQYDVQQGEwJTRzERMA8GA1UECAwIQWxpekxh\n\
bmQxETAPBgNVBAcMCEFsaXpMYW5kMQ0wCwYDVQQKDARBbGl6MQ0wCwYDVQQLDARB\n\
bGl6MSkwJwYDVQQDDCBtYW5hZ2VtZW50LmhvbWUuZ2FtZXNmYWlyeS5jby51azCC\n\
ASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALB2CmP1mfbpNw1WAO4DEUfR\n\
YeCY75Plh4NfgwnlL6N70f/jsWL6JaKgDWWYIN3oLspm94IYnwjz75eo8XuA5i6R\n\
lMxboK+xGH7+6zq0r4363iQXufqnAqs3De39CuAEbwpAC8oF48O0dv6G9iWEM4Y+\n\
Cdovf13Pl5krArho0jt0fMoSIB/zNZIRy4rf/ISCpqKUroUX4wkgUe2BxPefEMfp\n\
gjn2WdxkQp7fJaRs+14iSl2+swQ9deqbuCEw41ACTdsFdMrWmsa4yGx2cy6unnWB\n\
rxj2B0qyWECTGzVl4X0WVOARgoJJBeT31oq66h1c7T0d+FOlyhhZOaD9RNoKShMC\n\
AwEAAaOB7TCB6jAdBgNVHQ4EFgQUbbJdv60SOpsAy0So32oBQvL0JR8wgboGA1Ud\n\
IwSBsjCBr4AUbbJdv60SOpsAy0So32oBQvL0JR+hgYCkfjB8MQswCQYDVQQGEwJT\n\
RzERMA8GA1UECAwIQWxpekxhbmQxETAPBgNVBAcMCEFsaXpMYW5kMQ0wCwYDVQQK\n\
DARBbGl6MQ0wCwYDVQQLDARBbGl6MSkwJwYDVQQDDCBtYW5hZ2VtZW50LmhvbWUu\n\
Z2FtZXNmYWlyeS5jby51a4IUaZQpYmEbkAMKXcodM6DqVKWoALowDAYDVR0TBAUw\n\
AwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAZuNFr6UHn3jnk4t7PISnOGF0xd5P9+rZ\n\
OOq3Yep/5Kkp+zv3t6K+pFLxatGtwjhXFcnHCI2vXuj4RUfKXcHbY9+5+9WMHp7U\n\
/PwNMaNl4uzleZ4Pi/32kqbZaXBMzLNDl2p7KxHayO7HNC/Npk88wxzSGfNEhM+/\n\
56j0aVQxNEFjeJQlcIkR5gwk0lZi0tBnXaxSwogqQcZZlpgmuEfz11Uj1w39Xr1n\n\
XVG7etO7K4kzxixuAZ2pUym/xbdLcQ2ivgemkyeIHkg1z53Rh2hrhN4Zz8s9zXC1\n\
mV1h7VK9GnHz09oj9EzxkKsD1Z2I+/zq8+uDglfANm1e8kC5VycSpA==\n\
-----END CERTIFICATE-----";

char* clientCert = (char*)
"-----BEGIN CERTIFICATE-----\n\
MIIDZDCCAkygAwIBAgIUfkPRFljUTVTQXnUeek+G3KIdUQQwDQYJKoZIhvcNAQEL\n\
BQAwfDELMAkGA1UEBhMCU0cxETAPBgNVBAgMCEFsaXpMYW5kMREwDwYDVQQHDAhB\n\
bGl6TGFuZDENMAsGA1UECgwEQWxpejENMAsGA1UECwwEQWxpejEpMCcGA1UEAwwg\n\
bWFuYWdlbWVudC5ob21lLmdhbWVzZmFpcnkuY28udWswHhcNMjEwNzEwMTUzMzUx\n\
WhcNMjEwODA5MTUzMzUxWjBcMQswCQYDVQQGEwJTRzERMA8GA1UECAwIQWxpekxh\n\
bmQxDTALBgNVBAcMBEFsaXoxKzApBgNVBAMMImFjY2Vzcy5tYW5hZ2VtZW50Lmdh\n\
bWVzZmFpcnkuY28udWswggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDh\n\
msukW8ui/Y7DvyWpgS5hl8k2EcGixSyu6P44OWwjChutCgqsH5+dORpo7A8uNBv6\n\
aCt2uJ7yYtKgjKbf/Do7L8m6mK7jueF40/rtiroPL3kfiZ/CasUrmcWTMdimP1kT\n\
O2srcHy+cfFb+T8dXf2VOU2Lxfj41LpSvLOiM+ZsH2skpZNPKiwBXdsz1RHnjiN8\n\
uNmyw5/TYY+RPY55fv+F7HgnuFW63FrDHHfXqeD6/kC5y/1bBS6FuOcBnaMT1Zk4\n\
CsrnhIomA9HfUSYIO/j/HRM6FA/9IfcLD/pFfbuuT1Ip0HAzzuG6ol+QhW4bDqY1\n\
ynVMOqHW9R//aaFVBXR7AgMBAAEwDQYJKoZIhvcNAQELBQADggEBAHb6kUFyQ7CM\n\
TPC43PJh+sgDJl4afLaYPOu6ejTTcCqhxb2Ghsmt2QO7IjylC3vJeBdadV8rolm6\n\
1KL7HKfra4yYSD86pk4ldVi5gueAVPLIbq2sD+yJ+1jlNBFpt65j9IbBR2Uu8oSg\n\
FB7XlMRZWkAi4nO2uGLCZDN1wU9hgmzFBCUwtAz5REOszdwmGbH0UpRUdY5A43MN\n\
XnXV7Hs/lKs/CpM4231lCL59PzIuB4MCP2XJVNbKxEKZYeFYp70gRpioiEg8qv+h\n\
7zUlAYuzq9L8PU49d9YRowos4MRQVoGPYtZuGJ8cOphkqaCPQ2YrgK2E6L/3IcWg\n\
oIIPBoT/zvM=\n\
-----END CERTIFICATE-----";

char* clientKey = (char*)
"-----BEGIN PRIVATE KEY-----\n\
MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDhmsukW8ui/Y7D\n\
vyWpgS5hl8k2EcGixSyu6P44OWwjChutCgqsH5+dORpo7A8uNBv6aCt2uJ7yYtKg\n\
jKbf/Do7L8m6mK7jueF40/rtiroPL3kfiZ/CasUrmcWTMdimP1kTO2srcHy+cfFb\n\
+T8dXf2VOU2Lxfj41LpSvLOiM+ZsH2skpZNPKiwBXdsz1RHnjiN8uNmyw5/TYY+R\n\
PY55fv+F7HgnuFW63FrDHHfXqeD6/kC5y/1bBS6FuOcBnaMT1Zk4CsrnhIomA9Hf\n\
USYIO/j/HRM6FA/9IfcLD/pFfbuuT1Ip0HAzzuG6ol+QhW4bDqY1ynVMOqHW9R//\n\
aaFVBXR7AgMBAAECggEAKlPosUWnx0TbbE6IumzKTvUzgzmBoxBrecWtLM9ZQpm6\n\
55RivDiSseTs15KypnCQb0LsJLIu4Ds6WXUKOiwQoNoudxv+dCuD6i+bfMXycrbt\n\
esVPfCKcK7oGH7/Sbh6kj78uNFA+l1y5dBAnj1L7KOw/aGIUfFstOii9a0lhihdg\n\
sjZTFakyTKyPds7mXKqWCf3kgHlinTi/rx8zEf2tt+wxO3HRjdxf4n42tu0pYigo\n\
XOMUjB81nyWy+BwZSJjc1WNrSHDuW1EJSlVqTkvVi5lmFMHuoBmCD1SNIH9ILECA\n\
aIxGw5lbAkLJyvB5Tazo6VI+KGu6QgsC0WBzf3BbwQKBgQD8J7vh4GJ/sMMQv1bb\n\
EYsQeE6F3wer8DzE9ELpPrUwHgVHPXA4KNn5P54eval7Jp12MvwiaMY2higwvB6C\n\
yinoGdK3Re5/qxqjsjzlQKNjmr7OGuRLCz4+Z/tFoDUZNatMIhwDPMdUqPRgsBEE\n\
YlTw6Scm8X/Qrtn3iSz0lqpexQKBgQDlC2x/Yd2o3ImMl4Eax6sTQUs2YVpJBwzf\n\
GkENza1Vs6W1q2z8w9p0MRY5WTaF0q4wMEvpSXG7kmaHWQDYkemJ2MJOWIu9RnUo\n\
8U/Ix80iz9H+NNbBvOvWbvohTZUSKIMdU47MPSXkxRvW8zqHaFCjrleIbYL22GGt\n\
c1Zjyxm6PwKBgQDmjCnTx0Yn++UOXfO7Dto4b9dTvW0VPu1BIxg+jJA7c2deEIWX\n\
Q3qw0wLulnjsWY0k8k7n4yY/2f/LN2UqLk+MoHeyDGWZI0eTHjdhYO1C98y3Q40y\n\
NBBwHMB4k5eY+iIp1RIJv7t845G1CaY1fPau4m5iw/IaSpSOKEULSOpzBQKBgBPp\n\
D1BvcHZaXXakQOvUCZIN7fzXL6MDguHuBVOu2m+Fw1TshvfeCqJpFfZ8Q9oUO2Ij\n\
AKZR5RoaGuGPIhyxamy6NAHdfqBAfLTHbVkVzUZGbIm9jCGhS5sDYKj+doPyk5s8\n\
BUDJ2/5sCASCdkcJEWF5KVDJvEW6/5q1WQApyp2/AoGBAPhsjzv5ifZSbyn2tfAf\n\
tRupER12acFYYP8P9y3h2le1eVrCpeGOG6OIB7Rg7xg4xQott7VpbCBde3PN6i20\n\
0VMM2s7nB6uGVX3kxlMXIh3acr+s0BGfZ4Z1/PLYJI3PNiE2LmLAUVRaynXcp/1l\n\
CVq3bWJaMuChsbOqZbmA3aZO\n\
-----END PRIVATE KEY-----";

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(https, canConnect)
{
	try
	{
		unsigned long res = getPowerState(IP, cacrt, clientCert, clientKey);
	}
	catch (std::exception &e)
	{
		FAIL() << e.what();
		throw;
	}
}

TEST(https, failsWhenNoClientKeyProvided)
{
	try
	{
		unsigned long res = getPowerState(IP, cacrt, NULL, NULL);
	}
	catch (curlException &e)
	{
		if (e.errorCode == CURLcode::CURLE_SSL_CONNECT_ERROR)
			return;
		FAIL() << "Incorrect exception was thrown: " << e.errorCode;
	}
	catch (std::exception &e)
	{
		FAIL() << e.what();
		throw;
	}

	FAIL() << "No exception was thrown";
}

TEST(https, failsWhenNoCACertProvided)
{
	try
	{
		unsigned long res = getPowerState(IP, NULL, clientCert, clientKey);
	}
	catch (curlException &e)
	{
		if (e.errorCode == CURLcode::CURLE_PEER_FAILED_VERIFICATION)
		{
			// This is what we'd expect.
			return;
		}
		FAIL() << "Incorrect exception was thrown: " << e.errorCode;
	}
	catch (std::exception &e)
	{
		FAIL() << e.what();
		throw;
	}

	FAIL() << "No exception was thrown";
}

TEST(https, canReset)
{
	try
	{
		doReset(IP, cacrt, clientCert, clientKey);
	}
	catch (std::exception &e)
	{
		FAIL() << e.what();
		throw;
	}
}