#pragma once

extern const char *WIFI_SSID;
extern const char *WIFI_PASSWORD;

// mDNSホスト名(http://env-measure.local/ でアクセス可能にする)
extern const char *MDNS_HOSTNAME;

// AtomS3 Lite Port A (Grove) の I2C ピン
constexpr int I2C_SDA = 2;
constexpr int I2C_SCL = 1;
