#include <ESP8266WiFi.h>
#include "Adafruit_Si7021.h"
#include "Wire.h"
#include "Ambient.h"

Adafruit_Si7021 sensor = Adafruit_Si7021();  // Adafruit_Si7021オブジェクトを初期化する

WiFiClient client;
Ambient ambient;

const char* ssid = "ssid";
const char* password = "password";

unsigned int channelId = 100; // AmbientのチャネルID
const char* writeKey = "writeKey"; // ライトキー

void setup() {
    Serial.begin(74880);
    while (!Serial) ;

    Wire.begin(14, 13);
    if (!sensor.begin()) {  // Si7021を初期化する
        Serial.println("Did not find Si7021 sensor!");
        while (true) ;
    }

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.print("WiFi connected\r\nIP address: ");
    Serial.println(WiFi.localIP());

    ambient.begin(channelId, writeKey, &client); // チャネルIDとライトキーを指定してAmbientの初期化
}

void loop() {
    float temp = sensor.readTemperature();
    float humid = sensor.readHumidity();

    Serial.print("Humidity:    ");
    Serial.print(humid, 2);  // Si7021から湿度を読む
    Serial.print("\tTemperature: ");
    Serial.println(temp, 2);  // Si7021から温度を読む

    // 温度、湿度の値をAmbientに送信する
    ambient.set(1, temp);
    ambient.set(2, humid);

    ambient.send();

    delay(5 * 1000);
}
