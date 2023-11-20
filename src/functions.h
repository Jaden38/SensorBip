#include <Arduino.h>

unsigned long lastBeepTime = 0;

void beep(int pin, int frequency, int duration)
{
    tone(pin, frequency, duration);
}

void beepFromDistance(int distance, int BUZZER_PIN, int duree)
{
    int currentTime = millis(); 
    int endTime = currentTime + 2000;

    for(int i =currentTime; i< endTime; i+duree){
        beep(BUZZER_PIN, 10000, duree);
    }
}




int getDistance(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);

  int distance = (duration / 2) / 29.1;
  Serial.println("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}