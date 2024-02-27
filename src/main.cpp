#include <Arduino.h>
#include <WiFi.h>
// Header file of ssid, password and discord hook
#include "Secret.h"

#include <HTTPClient.h>

#include <WiFiClientSecure.h>


const char server[] = "discord.com";
const int port = 443;

// WiFiClient client;
// WiFiClientSecure client;
// HttpClient http_client = HttpClient(client, server, port);

void setup()
{
    delay(5000);
    Serial.begin(115200);
    WiFi.begin(SSID, PWD);
    WiFi.mode(WIFI_MODE_STA);
    delay(5000);
    while (WiFi.status() != WL_CONNECTED)
    {
        WiFi.reconnect();
        Serial.print("Connecting to WiFi: ");
        Serial.print(SSID);
        Serial.println();
        delay(1000);
    }

    Serial.print("WiFI Connected to ");
    Serial.print(SSID);
    Serial.println();
}

const char json[] PROGMEM =
    R"rawliteral(
{"content":"This is a message from ESP32"}
        )rawliteral";


void loop()
{
    WiFiClientSecure *client = new WiFiClientSecure;

    if (client)
    {
        // just ignore it
        client->setInsecure();
        {
            HTTPClient https;

            Serial.print("Hello");
            Serial.println();

            String content = "This is a message from ESP32";
            https.begin(*client, DISCORD_HOOK);
            https.addHeader("Content-Type", "application/json");
            https.POST(json);
            https.end();
        }
        delete client;
    }

    delay(1000);
}
