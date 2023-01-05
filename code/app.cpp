#include <ESP8266WiFi.h>
#include <ESP8266WebServerSecure.h>
#include <time.h>
#include <WiFiUdp.h>
#include <sstream>

#include "board.h"
#include "config.h"
#include "app.h"

extern const char serverCert[];
extern const char serverKey[];
extern const char clientAuthCert[];

char* PROGMEM pageRoot = "<html>\
<head></head>\
<a href=\"doPower\">Power button control</a></br>\
<a href=\"doReset\">Reset button control</a></br>\
<a href=\"getTargetStatus\">Get target power LED state</a></br>\
</html>";

char* PROGMEM pageReset = "<form method=post>\
<input type=\"submit\">Tap reset button</br>\
</form>";

char* PROGMEM pagePower =  "<form method=post>\
<input type=\"submit\" name=\"thingToDo\" value=\"short\">Do short power button press</input></br>\
<input type=\"submit\" name=\"thingToDo\" value=\"long\">Do long power button press</input></br>\
</form>";

app::app()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(PIN_POWERBUTTON, OUTPUT);
	pinMode(PIN_RESETBUTTON, OUTPUT);

	Serial.begin(115200);

	connectwifi();

	serverHTTP = new ESP8266WebServerSecure(443);
	serverHTTP->getServer().setClientTrustAnchor(new BearSSL::X509List(clientAuthCert));
	serverHTTP->getServer().setRSACert(new BearSSL::X509List(serverCert), new BearSSL::PrivateKey(serverKey));
	serverHTTP->on("/", std::bind(&app::showPageRoot, this));
	serverHTTP->on("/doPower", std::bind(&app::showPage_doPowerButton, this));
	serverHTTP->on("/doReset", std::bind(&app::showPage_doResetButton, this));
	serverHTTP->on("/getTargetStatus", std::bind(&app::showPage_getTargetStatus, this));
	serverHTTP->begin();
}


app::~app()
{
	delete serverHTTP;
}

void app::setClock()
{
	configTime(3 * 3600, 0, "pool.ntp.org", "time.nist.gov");

	time_t now = time(nullptr);
	while (now < 8 * 3600 * 2) {
		delay(500);
		//Serial.print(".");
		now = time(nullptr);
	}
	struct tm timeinfo;
	gmtime_r(&now, &timeinfo);
	Serial.print("OK. Current time: ");
	Serial.println(asctime(&timeinfo));
}

void app::connectwifi()
{
	Serial.println("Connecting to wifi...");

	WiFi.begin(CFG_WIFI_SSID, CFG_WIFI_PASSWORD);

	// Wait for wifi negotiation and DHCP
	while (WiFi.status() != WL_CONNECTED)
		delay(500);

	Serial.print("wifi up, IP: ");
	for (unsigned char n = 0; n < 4; n++)
	{
		Serial.print(WiFi.localIP()[n]);
		if (n < 3)
			Serial.print('.');
	}
	Serial.print("\r\n");

	Serial.print("doing NTP sync..");
	setClock();
}

void app::idleForever()
{
	// Since some hardware will PWM the 'power on LED', we keep a count of how long it has been since we last saw a HIGH state.
	// If we saw any HIGH state in the last 100ms, we interpret the LED as powered on.
	unsigned long timeOfLastPowerLEDHigh = 0;
	while (true)
	{
		if (digitalRead(PIN_POWERSENSOR) == LOW)	// This signal is active low, remember.
		{
			timeOfLastPowerLEDHigh = millis();
		}
		// Has the power LED been asserted in the last 100msec?
		if (millis() - timeOfLastPowerLEDHigh > 100)
			targetPowerLEDState = false;
		else
			targetPowerLEDState = true;

		serverHTTP->handleClient();
	}
}

void app::showPageRoot()
{
	serverHTTP->send(200, "text/html", pageRoot);
}

void app::showPage_doPowerButton()
{
	if (serverHTTP->method() == HTTPMethod::HTTP_GET)
	{
		serverHTTP->send(200, "text/html", pagePower);
	}
	else if (serverHTTP->method() == HTTPMethod::HTTP_POST)
	{
		if (serverHTTP->arg("thingToDo") == "long")
		{
			digitalWrite(PIN_POWERBUTTON, HIGH);
			delay(5500);
			digitalWrite(PIN_POWERBUTTON, LOW);

			serverHTTP->send(200, "text/html", "OK");
		}
		else if (serverHTTP->arg("thingToDo") == "short")
		{
			digitalWrite(PIN_POWERBUTTON, HIGH);
			delay(500);
			digitalWrite(PIN_POWERBUTTON, LOW);

			serverHTTP->send(200, "text/html", "OK");
		}
		else if (serverHTTP->arg("thingToDo") == "short")
		{
			serverHTTP->send(400, "text/html", "bad thingToDo arg");
		}
	}
	else
	{
		serverHTTP->send(405, "text/html", "Bad method");
	}
}

void app::showPage_doResetButton()
{
	if (serverHTTP->method() == HTTPMethod::HTTP_GET)
	{
		serverHTTP->send(200, "text/html", pageReset);
	}
	else if (serverHTTP->method() == HTTPMethod::HTTP_POST)
	{
		digitalWrite(PIN_RESETBUTTON, HIGH);
		delay(500);
		digitalWrite(PIN_RESETBUTTON, LOW);
		serverHTTP->send(200, "text/html", "OK");
	}
	else
	{
		serverHTTP->send(405, "text/html", "Bad method");
	}
}

void app::showPage_getTargetStatus()
{
  char* state;
	if (targetPowerLEDState)
		state = "ON";
	else
		state = "OFF";
	serverHTTP->send(200, "text/html", state);
}
