/*
 * ESP8266とBME280をI2C接続し、温度、湿度、気圧を測定しプリントアプトする
 * Boschライブラリーを使う
 */
#include <Wire.h>
#include "bme280_i2c.h"

#define SDA 14
#define SCL 13

BME280 bme280(BME280_I2C_ADDR_PRIM);

void setup(){
    Wire.begin(SDA, SCL);
    pinMode(SDA, INPUT_PULLUP); // SDAピンのプルアップの指定
    pinMode(SCL, INPUT_PULLUP); // SCLピンのプルアップの指定

    Serial.begin(74880);
    Serial.print("\r\nBME280 test\r\n");

    bme280.begin(); // BME280の初期化
}

void loop() {
    int8_t rslt;
    struct bme280_data data;

    rslt = bme280.get_sensor_data(&data);
    Serial.printf("%0.2f, %0.2f, %0.2f\r\n", data.temperature, data.humidity, data.pressure / 100);

    delay(3000);
}
