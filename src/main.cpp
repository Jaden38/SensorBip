#include <Arduino.h>

#define BUZZER_PIN 12

void setup()
{
  pinMode(BUZZER_PIN, OUTPUT);
}

void beep(int pin, int frequency, int duration)
{
  tone(pin, frequency, duration);
  delay(duration + 50);
}

void loop()
{

  // for (int i = 0; i < 1; ++i)
  // {
  //   beep(BUZZER_PIN, 5000, 500);
  //   beep(BUZZER_PIN, 10000, 500);
  //   beep(BUZZER_PIN, 2000, 500);
  //   beep(BUZZER_PIN, 16000, 500);
  //   beep(BUZZER_PIN, 20000, 500);
  //   delay(1000);
  // }
}
