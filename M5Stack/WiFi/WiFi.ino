#include <M5Stack.h>
#include <WiFi.h>

const char* ssid = "Buffalo-G-8080";    // この場所のSSID（2.4GHzの）
const char* password = "duftsfmu7fg4s";    // SSIDに対応するパスワード

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(2);

    WiFi.begin(ssid, password);    // Wi-Fi APに接続する
    while (WiFi.status() != WL_CONNECTED) {    //  Wi-Fi AP接続待ち
        delay(500);
        M5.Lcd.print('.');
    }
    M5.Lcd.print("\r\nWiFi connected\r\nIP address: ");
    M5.Lcd.println(WiFi.localIP());    // このM5Stackに割り当てられたIPアドレス
}

void loop() {
    //  何もしない
}
