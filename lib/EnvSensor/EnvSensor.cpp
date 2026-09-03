#include "EnvSensor.h"

#include <Wire.h>
/**
 * 環境センサーの初期化と読み取りを行うクラスの実装
 */
bool EnvSensor::begin(int sda, int scl) {
  Wire.begin(sda, scl);
  bool ok1 = sht3x_.begin(&Wire, SHT3X_I2C_ADDR, sda, scl, 400000U);
  bool ok2 = qmp6988_.begin(&Wire, QMP6988_SLAVE_ADDRESS_L, sda, scl, 400000U);
  return ok1 && ok2;
}
/**
 * 環境センサーの現在値を取得する
 */
SensorData EnvSensor::read() {
  if (sht3x_.update()) {
    last_.temperature = sht3x_.cTemp;
    last_.humidity = sht3x_.humidity;
  }
  if (qmp6988_.update()) {
    last_.pressure = qmp6988_.pressure / 100.0f; // Pa -> hPa
  }
  return last_;
}
