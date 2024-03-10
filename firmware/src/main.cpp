#include <Arduino.h>
#include <WiFi.h>
#include <ESPAdmin.h>
#include <credentials.h>

ESPAdmin::Logger logger("app");

void onCustomCommand(String message);
unsigned int viewersCount = 0;

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
  if (message == R"({"key":"Viewer_Count","value":"{\"viewer\":\"count\"}"})")
  {
    logger.info("%d users are currently watching", viewersCount);
  }
  else if (message == R"({"key":"Viewer_Reset","value":"{\"viewer\":\"reset\"}"})")
  {
    viewersCount = 0;
  }
  else if (message == R"({"viewer":true})")
  {
    viewersCount++;
  }
  else if (message == R"({"viewer":false})")
  {
    if (viewersCount > 0)
    {
      viewersCount--;
    }
  }
}

void loop()
{
  if (viewersCount > 0)
  {
    static int counter = 0;
    ESPAdmin::MQTT::publish("/cam/stream", String(counter), 0, false);
    counter++;
  }

  delay(50);
}