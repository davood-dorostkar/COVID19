#include <Arduino.h>
#include <Servo.h>
Servo servo;
#define trigger 2
#define echo 3
#define servoPin 6
int len = 10;
// float frame[10];
// int len = (sizeof(frame) / sizeof(float));
float avgDistance;

void spray()
{
  // Serial.println("spray");
  servo.write(180);
  delay(1000);
  servo.write(0);
}

// void refreshFrame(float newFrame)
// {
//   for (int i = 1; i < len; i++)
//   {
//     frame[i - 1] = frame[i];
//   }
//   frame[len - 1] = newFrame;
// }

// float meanFrame()
// {
//   float avg = 0;
//   for (int i = 0; i < len; i++)
//     avg += frame[i];
//   return (avg / (float)len);
// }

// void printFrame()
// {
//   for (int i = 0; i < len; i++)
//     Serial.print((String)frame[i] + " ");
//   Serial.print("\n");
// }

float measure()
{
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  float time = pulseIn(echo, HIGH);
  float velocity = 334;
  float distance = ((time / 2) * velocity) * 0.0001; // conversion to cm
  return distance;
}

float meanSimple()
{
  float data = 0;
  for (int i = 0; i < len; i++)
  {
    data += measure();
  }
  return (data / (float)len);
}

void checkForDistance()
{
  if (avgDistance >= 2 && avgDistance <= 10)
  {
    spray();
    delay(2000);
  }
  else
  {
    Serial.println(avgDistance);
    servo.read();
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  servo.attach(servoPin);
  servo.write(0);
  //for (int i = 0; i < len; i++)
  //  refreshFrame(measure());
}

void loop()
{
  //refreshFrame(measure());
  //avgDistance = meanFrame();
  avgDistance = meanSimple();
  checkForDistance();
  delay(300);
}
