#include "WifiManager.h"

#include <Arduino.h>
#include <ESPmDNS.h>
#include <WiFi.h>
/**
 * WiFi接続とmDNSの管理を行うクラスの実装
 */
void WifiManager::connect(const char *ssid, const char *password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}
/**
 * mDNSを開始する
 * @param hostname ホスト名
 * @return 成功した場合はtrue、失敗した場合はfalse
 */
bool WifiManager::startMdns(const char *hostname) {
  if (!MDNS.begin(hostname)) {
    return false;
  }
  MDNS.addService("http", "tcp", 80);
  return true;
}
