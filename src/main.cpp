#include <Arduino.h>
#include <M5AtomS3.h>

#include "ApiServer.h"
#include "EnvSensor.h"
#include "WifiManager.h"
#include "config.h"

EnvSensor sensor;
WifiManager wifiManager;
ApiServer apiServer(sensor);
/**
 * 起動時に呼ばれる関数
 */
void setup() {
  AtomS3.begin(true);
  AtomS3.dis.setBrightness(50);

  sensor.begin(I2C_SDA, I2C_SCL);

  wifiManager.connect(WIFI_SSID, WIFI_PASSWORD);
  wifiManager.startMdns(MDNS_HOSTNAME);

  apiServer.begin();
}

/**
 * メインループ関数
 * 継続的に呼ばれる
 */
void loop() {
  AtomS3.update();
  apiServer.handleClient();
  delay(1); // CPU負荷・発熱を抑えるための小休止
}
