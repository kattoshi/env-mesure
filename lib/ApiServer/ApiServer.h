#pragma once

#include <WebServer.h>

#include "EnvSensor.h"

// REST APIのルーティングとレスポンス生成を担当するAPI層
class ApiServer {
 public:
  /**
   * @brief コンストラクタ
   * @param sensor 測定値の取得元となるEnvSensorの参照
   * @param port 待ち受けるHTTPポート番号
   */
  explicit ApiServer(EnvSensor &sensor, uint16_t port = 80);

  /** @brief ルート登録を行いHTTPサーバを開始する */
  void begin();

  /** @brief 受信済みのHTTPリクエストを処理する(loopから連続呼び出し) */
  void handleClient();

 private:
  // GET /current のハンドラ: 現在値をJSONで返却
  void handleCurrent();
  // 未定義のパスにアクセスされた場合の応答
  void handleNotFound();

  EnvSensor &sensor_;
  WebServer server_;
};
