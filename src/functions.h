#include <Arduino.h>

unsigned long lastBeepTime = 0;

void beep(int pin, int frequency, int duration, int beepDelay)
{
    tone(pin, frequency, duration);
    delay(beepDelay);

}

int beepFromDistance(int distance, int BUZZER_PIN, int duree, int beepDelay, int lastTime, int LoopDelay, int freq)
{
    int currentTime = lastTime;

    while(currentTime  <= lastTime + LoopDelay)
    {
        currentTime = millis();
        Serial.println(currentTime);
        beep(BUZZER_PIN, freq, 100, beepDelay);
    } 
    lastTime = currentTime;
    //Serial.println("lastTime: ");
    //Serial.println(lastTime);
    return lastTime;
}




int getDistance(int trig, int echo){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);

  int distance = (duration / 2) / 29.1;
  //Serial.println("Distance: ");
  //Serial.print(distance);
  //Serial.println(" cm");

  return distance;
}