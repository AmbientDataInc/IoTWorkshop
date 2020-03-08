#include <M5Stack.h>
#include "Seeed_SHT35.h"

#define SCLPIN  22

SHT35 sensor(SCLPIN);

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(2);

    if(sensor.init()) {
        M5.Lcd.println("sensor init failed!!!");
    }
}

void loop() {
    float temp,hum;
    if(NO_ERROR!=sensor.read_meas_data_single_shot(HIGH_REP_WITH_STRCH,&temp,&hum)) {
        M5.Lcd.println("sensor read failed!!");
    } else {
        M5.Lcd.fillScreen(BLACK);
        M5.Lcd.setCursor(60,80);
        M5.Lcd.printf("temp: %.1f 'C", temp);

        M5.Lcd.setCursor(60,140);
        M5.Lcd.printf("humid: %.1f %%", hum);
    }
    delay(1000);
}
