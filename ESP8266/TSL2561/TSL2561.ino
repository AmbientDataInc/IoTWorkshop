#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>

Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

void setup(void) {
    Serial.begin(74880);
    Serial.println("Light Sensor Test"); Serial.println("");
  
    Wire.begin(14, 13);
    if(!tsl.begin(&Wire)) {
      /* There was a problem detecting the TSL2561 ... check your connections */
      Serial.print("Ooops, no TSL2561 detected ... Check your wiring or I2C ADDR!");
      while(1) delay(0);
    }

    tsl.enableAutoRange(true);            /* Auto-gain ... switches automatically between 1x and 16x */
    tsl.setIntegrationTime(TSL2561_INTEGRATIONTIME_13MS);      /* fast but low resolution */
}

void loop(void) {
    sensors_event_t event;  /* Get a new sensor event */
    tsl.getEvent(&event);
 
    /* Display the results (light is measured in lux) */
    if (event.light) {
      Serial.print(event.light); Serial.println(" lux");
    } else {
        /* If event.light = 0 lux the sensor is probably saturated
           and no reliable data could be generated! */
        Serial.println("Sensor overload");
    }
    delay(250);
}
