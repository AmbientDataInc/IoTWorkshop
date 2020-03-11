#include <M5Stack.h>
#include "Seeed_SHT35.h"
#include <WiFi.h>
#include <Ambient.h>

#define SCLPIN  22

SHT35 sensor(SCLPIN);

const char* ssid = "myssid";    // この場所のSSID（2.4GHzの）
const char* password = "password";    // SSIDに対応するパスワード

unsigned int channelId = 100;
const char* writeKey = "writeKey";

WiFiClient client;
Ambient am;  // Ambientオブジェクトを作る

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(2);

    if(sensor.init()) {
        M5.Lcd.println("sensor init failed!!!");
    }

    WiFi.begin(ssid, password);    // Wi-Fi APに接続する
    while (WiFi.status() != WL_CONNECTED) {    //  Wi-Fi AP接続待ち
        delay(500);
        M5.Lcd.print('.');
    }
    M5.Lcd.print("\r\nWiFi connected\r\nIP address: ");
    M5.Lcd.println(WiFi.localIP());    // このM5Stackに割り当てられたIPアドレス

    am.begin(channelId, writeKey, &client);

    float temp,hum;
    if(NO_ERROR!=sensor.read_meas_data_single_shot(HIGH_REP_WITH_STRCH,&temp,&hum)) {
        M5.Lcd.println("sensor read failed!!");
    } else {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(60,80);
        M5.Lcd.printf("temp: %.1f 'C", temp);

        M5.Lcd.setCursor(60,140);
        M5.Lcd.printf("humid: %.1f %%", hum);

        am.set(1, temp);
        am.set(2, hum);
        am.send();
    }
    esp_deep_sleep(5000*1000);
}

void loop() {
}
