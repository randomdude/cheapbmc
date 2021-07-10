#include <ESP8266WiFi.h>
#include <ESP8266WebServerSecure.h>
#include <time.h>

#include <WiFiUdp.h>

#include "app.h"


void setup()
{
	ESP.wdtDisable();
	*((volatile uint32_t*)0x60000900) &= ~(1); // Hardware WDT OFF
}

void loop()
{
	app theapp;

	ESP.wdtDisable();
	*((volatile uint32_t*)0x60000900) &= ~(1); // Hardware WDT OFF
	theapp.idleForever();
}
