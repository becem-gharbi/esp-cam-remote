#include <Arduino.h>
#include <WiFi.h>
#include <ESPAdmin.h>
#include <credentials.h>
#include <esp_camera.h>

#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

ESPAdmin::Logger logger("app");

void onCustomCommand(String message);
void setupCamera(int quality);
unsigned int viewersCount = 0;

void setup()
{
  setCpuFrequencyMhz(240);

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

  setupCamera(30);
}

void loop()
{
  if (viewersCount > 0)
  {
    camera_fb_t *frame = esp_camera_fb_get();

    ESPAdmin::MQTT::publish("/cam/stream", (char *)frame->buf, frame->len, 0, false);

    esp_camera_fb_return(frame);
    frame = NULL;
  }
  else
  {
    delay(50);
  }
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

void setupCamera(int quality)
{
  const camera_config_t _camConfig = {
      .pin_pwdn = PWDN_GPIO_NUM,
      .pin_reset = RESET_GPIO_NUM,
      .pin_xclk = XCLK_GPIO_NUM,
      .pin_sscb_sda = SIOD_GPIO_NUM,
      .pin_sscb_scl = SIOC_GPIO_NUM,
      .pin_d7 = Y9_GPIO_NUM,
      .pin_d6 = Y8_GPIO_NUM,
      .pin_d5 = Y7_GPIO_NUM,
      .pin_d4 = Y6_GPIO_NUM,
      .pin_d3 = Y5_GPIO_NUM,
      .pin_d2 = Y4_GPIO_NUM,
      .pin_d1 = Y3_GPIO_NUM,
      .pin_d0 = Y2_GPIO_NUM,
      .pin_vsync = VSYNC_GPIO_NUM,
      .pin_href = HREF_GPIO_NUM,
      .pin_pclk = PCLK_GPIO_NUM,
      .xclk_freq_hz = 20000000,
      .pixel_format = PIXFORMAT_JPEG,
      .frame_size = FRAMESIZE_HVGA,
      .jpeg_quality = quality,
      .fb_count = 1,
      .grab_mode = CAMERA_GRAB_WHEN_EMPTY,
  };

  esp_err_t err = esp_camera_init(&_camConfig);

  if (err == ESP_OK)
  {
    logger.success("Camera ready");
  }
  else
  {
    logger.error("Failed to setup camera");
  }
}