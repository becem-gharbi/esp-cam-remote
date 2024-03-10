#include <Arduino.h>
#include <WiFi.h>
#include <ESPAdmin.h>
#include <credentials.h>

ESPAdmin::Logger logger("app");

void onCustomCommand(String message);

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  logger.info("WiFi wait");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  logger.success("WiFi connected");

  ESPAdmin::begin(httpHost, deviceId, apiKey, httpCert, mqttCert);

  ESPAdmin::Command::onCustom = &onCustomCommand;
}

void onCustomCommand(String message)
{
  logger.info(message.c_str());
}

void loop()
{
  static int counter = 0;
  ESPAdmin::MQTT::publish("/cam/stream", String(counter), 0, false);
  counter++;
  delay(50);
}