#pragma once

#include <M5UnitENV.h>

// センサーから得られる測定値
struct SensorData {
  float temperature = NAN; // 摂氏
  float humidity = NAN;    // %RH
  float pressure = NAN;    // hPa
};

// ENV3ユニット(SHT30 + QMP6988)を扱うセンサー層
class EnvSensor {
 public:
  /**
   * @brief I2Cを初期化しセンサーを開始する
   * @param sda I2C SDAピン番号
   * @param scl I2C SCLピン番号
   * @return 両センサーの初期化に成功したらtrue
   */
  bool begin(int sda, int scl);

  /**
   * @brief センサーを更新し最新値を返す(更新失敗時は直前の値を維持)
   * @return 最新の測定値
   */
  SensorData read();

 private:
  SHT3X sht3x_;
  QMP6988 qmp6988_;
  SensorData last_;
};
