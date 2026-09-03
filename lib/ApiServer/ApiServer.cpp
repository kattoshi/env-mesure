#include "ApiServer.h"
#include <M5AtomS3.h>

#include <ArduinoJson.h>
#include <cmath>

/**
 * コンストラクタ
 * @param sensor EnvSensorの参照
 * @param port サーバのポート番号
 */
ApiServer::ApiServer(EnvSensor &sensor, uint16_t port)
    : sensor_(sensor), server_(port) {}

/**
 * APIサーバを開始する
 */
void ApiServer::begin() {
  server_.on("/current", HTTP_GET, [this]() { handleCurrent(); });
  server_.onNotFound([this]() { handleNotFound(); });
  server_.begin();
}
/**
 * クライアントからのリクエストを処理する
 */
void ApiServer::handleClient() {
  server_.handleClient();
}

/**
 * GET /current のハンドラ: 現在値を取得してJSONで返す
 */
void ApiServer::handleCurrent() {
  AtomS3.dis.drawpix(0x00ff00);
  AtomS3.update();
  
  SensorData data = sensor_.read();

  AtomS3.dis.drawpix(0x000000);
  AtomS3.update();

  JsonDocument doc;
  doc["temp"] = std::round(data.temperature * 10.0f) / 10.0f;
  doc["pressure"] = std::round(data.pressure * 10.0f) / 10.0f;
  doc["humidity"] = std::round(data.humidity * 10.0f) / 10.0f;
  doc["cpu_temp"] = std::round(temperatureRead() * 10.0f) / 10.0f;

  String response;
  serializeJson(doc, response);
  server_.send(200, "application/json", response);
}

/**
 * 未定義のパスにアクセスされた場合のハンドラ
 */
void ApiServer::handleNotFound() {
  server_.send(404, "application/json", "{\"error\":\"not found\"}");
}
