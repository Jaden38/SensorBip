#include <Arduino.h>
#include <functions.h>

#define BUZZER_PIN 12
#define SENSOR_TRIG 32
#define SENSOR_ECHO 33

void setup()
{
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SENSOR_TRIG, OUTPUT);
  pinMode(SENSOR_ECHO, INPUT);
}

void loop()
{
  int distance = getDistance(SENSOR_TRIG, SENSOR_ECHO);
  
  switch(distance){
    case 0 ... 10:
      beepFromDistance(distance, BUZZER_PIN, 100);
      break;
    case 11 ... 20:
      beepFromDistance(distance, BUZZER_PIN, 200);
      break;
    case 21 ... 30:
      beepFromDistance(distance, BUZZER_PIN, 300);
      break;
    case 31 ... 40:
      beepFromDistance(distance, BUZZER_PIN, 400);
      break;
    case 41 ... 50:
      beepFromDistance(distance, BUZZER_PIN, 500);
      break;
  }
  delay(2000);
}
