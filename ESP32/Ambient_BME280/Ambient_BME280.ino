/*
 * ESP32とBME280をI2C接続し、温度、湿度、気圧を測定しプリントアプトする
 * Boschライブラリーを使う
 */
#include <WiFi.h>
#include <Wire.h>
#include "bme280_i2c.h"
#include "Ambient.h"

#define SDA 12
#define SCL 14

BME280 bme280(BME280_I2C_ADDR_PRIM);

WiFiClient client;
Ambient ambient;

const char* ssid = "ssid";
const char* password = "password";

unsigned int channelId = 100; // AmbientのチャネルID
const char* writeKey = "writeKey"; // ライトキー

void setup(){
    Wire.begin(SDA, SCL);
    pinMode(SDA, INPUT_PULLUP); // SDAピンのプルアップの指定
    pinMode(SCL, INPUT_PULLUP); // SCLピンのプルアップの指定

    Serial.begin(115200);
    Serial.print("\r\nBME280 test\r\n");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("WiFi connected\r\nIP address: ");
    Serial.println(WiFi.localIP());

    bme280.begin(); // BME280の初期化

    ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化
}

void loop() {
    unsigned long t = millis();
    int8_t rslt;
    struct bme280_data data;

    rslt = bme280.get_sensor_data(&data);
    Serial.printf("%0.2f, %0.2f, %0.2f\r\n", data.temperature, data.humidity, data.pressure / 100);

    // 温度、湿度、気圧、CO2、TVOCの値をAmbientに送信する
    ambient.set(1, String(data.temperature).c_str());
    ambient.set(2, String(data.humidity).c_str());
    ambient.set(3, String(data.pressure / 100).c_str());

    ambient.send();

    delay(5 * 1000 - (millis() - t));
}
