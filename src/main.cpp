#include <Arduino.h>
#include <functions.h>

#define BUZZER_PIN 12
#define SENSOR_TRIG 32
#define SENSOR_ECHO 33

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SENSOR_TRIG, OUTPUT);
  pinMode(SENSOR_ECHO, INPUT);
}



void loop()
{
  distance(SENSOR_TRIG,SENSOR_ECHO);
  delay(1000)
  // beepFromDistance(5, BUZZER_PIN);
}
