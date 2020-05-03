#include <Arduino.h>
#define trigger 2
#define echo 3
#define servo 4
float frame[50];
int len = (sizeof(frame) / sizeof(float));
int cursor;
float distance;
float avgDistance;

void setup()
{
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(servo, OUTPUT);
}

void spray()
{
  Serial.println("spray");
  analogWrite(servo, 255);
  delay(1000);
  analogWrite(servo, 0);
}

void refreshFrame()
{
  if (cursor == len - 1)
  {
    for (int i = 1; i = len - 1; i++)
    {
      frame[i - 1] = frame[i];
    }
  }
  else
    cursor++;
  frame[cursor] = distance;
}

void meanFrame()
{

  for (int i = 0; i = len - 1; i++)
  {
    avgDistance += frame[i];
    avgDistance /= len;
  }
}
void loop()
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  float time = pulseIn(echo, HIGH);
  float velocity = 334;
  distance = ((time / 2) * velocity) * 0.0001; // conversion to cm
  refreshFrame;
  meanFrame;
  if (avgDistance >= 2 && avgDistance <= 400)
  {
    //Serial.print("Distance= ");
    //Serial.println(distance);
    if (avgDistance < 7)
    {
      spray;
      delay(1000);
    }
    else
      Serial.println(avgDistance);
  }
  else
  {
    Serial.println("Out of range");
  }
  avgDistance = 0;
}
