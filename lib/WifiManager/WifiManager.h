#pragma once

// Wi-Fi接続とmDNSを扱うネットワーク層
class WifiManager {
 public:
  /**
   * @brief Wi-Fiに接続しIPアドレス取得まで待機する
   * @param ssid 接続先SSID
   * @param password 接続パスワード
   */
  void connect(const char *ssid, const char *password);

  /**
   * @brief mDNSを開始する(失敗してもfalseを返すだけで例外は投げない)
   * @param hostname 公開するホスト名("<hostname>.local"でアクセス可能になる)
   * @return 開始に成功したらtrue
   */
  bool startMdns(const char *hostname);
};
