/**
 * @file main.cpp
 * @author Elvandry Ghiffary (elvandry13@gmail.com)
 * @brief ESP32 MQTT Lamp Control
 * @version 0.1
 * @date 2020-04-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#include <WiFi.h>
#include <PubSubClient.h>

// Enter SSID and Password
const char *ssid = "WIFI_SSID";
const char *password = "WIFI_PASSWD";

// Enter MQTT Broker IP address
const char *mqtt_server = "MQTT_IP_ADDR";

// Enter MQTT security
const char *mqtt_user = "MQTT_USER";
const char *mqtt_pass = "MQTT_PASSWD";

// Wifi Client Class
WiFiClient espClient;

// Pubsub Client Class
PubSubClient client(espClient);

// LED Pin
const int ledPin = 13;

void setup_wifi()
{
	delay(10);
	// Connect to Wifi Network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
}

void callback(char *topic, byte *message, unsigned int length)
{
	Serial.print("Message arrived on topic: ");
	Serial.print(topic);
	Serial.print(". Message: ");
	String messageTemp;

	for (int i = 0; i < length; i++)
	{
		Serial.print((char)message[i]);
		messageTemp += (char)message[i];
	}
	Serial.println();

	if (String(topic) == "esp32/output")
	{
		Serial.print("Changing output to ");
		if (messageTemp == "on")
		{
			Serial.println("on");
			digitalWrite(ledPin, HIGH);
		}
		else if (messageTemp == "off")
		{
			Serial.println("off");
			digitalWrite(ledPin, LOW);
		}
	}
}

void reconnect()
{
	// Loop until we're reconnected
	while (!client.connected())
	{
		Serial.print("Attempting MQTT connection...");
		// Attempt to connect
		if (client.connect("ESP32Client", mqtt_user, mqtt_pass))
		{
			Serial.println("connected");
			// Subscribe
			client.subscribe("esp32/output");
		}
		else
		{
			Serial.print("failed, rc=");
			Serial.print(client.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void setup()
{
	// Serial Baud Rate
	Serial.begin(115200);

	// Wifi Setup
	setup_wifi();

	// MQTT Server Setup
	client.setServer(mqtt_server, 1883);
	client.setCallback(callback);

	// LED Pin Setup
	pinMode(ledPin, OUTPUT);
}

void loop()
{
	if (!client.connected())
	{
		reconnect();
	}
	client.loop();
}
