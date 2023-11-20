#include <Arduino.h>
#include <functions.h>
#include <notes.h>

#define BUZZER_PIN_1 12
#define SENSOR_TRIG 32
#define SENSOR_ECHO 33

void setup()
{
  Serial.begin(115200);
  pinMode(BUZZER_PIN_1, OUTPUT);
  pinMode(SENSOR_TRIG, OUTPUT);
  pinMode(SENSOR_ECHO, INPUT);
}

void loop()
{
  int distance = getDistance(SENSOR_TRIG, SENSOR_ECHO);
  int lastTime = 0;

  int beepDelay = map(distance,0, 60, 10,500 );
  Serial.println("beepDelay: ");
  Serial.println(beepDelay);
  beepFromDistance(distance, BUZZER_PIN_1, 100, beepDelay, lastTime);
}

