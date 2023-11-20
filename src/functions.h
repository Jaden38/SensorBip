#include <Arduino.h>

unsigned long lastBeepTime = 0;

void beepFromDistance(int distance, int BUZZER_PIN)
{
    unsigned long currentTime = millis();

    if (distance < 10 && currentTime - lastBeepTime > 500)
    {
        beep(BUZZER_PIN, 5000, 500);
        lastBeepTime = currentTime;
    }
    else if (distance < 20 && currentTime - lastBeepTime > 500)
    {
        beep(BUZZER_PIN, 10000, 500);
        lastBeepTime = currentTime;
    }
    else if (distance < 30 && currentTime - lastBeepTime > 500)
    {
        beep(BUZZER_PIN, 2000, 500);
        lastBeepTime = currentTime;
    }
    else if (distance < 40 && currentTime - lastBeepTime > 500)
    {
        beep(BUZZER_PIN, 16000, 500);
        lastBeepTime = currentTime;
    }
    else if (distance < 50 && currentTime - lastBeepTime > 500)
    {
        beep(BUZZER_PIN, 20000, 500);
        lastBeepTime = currentTime;
    }
}

void beep(int pin, int frequency, int duration)
{
    tone(pin, frequency, duration);
}


void distance(int trig, int echo){
    void distance(){
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  Serial.println(duration);

  int distance = (duration / 2) / 29.1;
  Serial.println("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
}