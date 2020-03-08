#include <M5Stack.h>

#define LED 5

void setup() {
  // put your setup code here, to run once:
  M5.begin();

  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
