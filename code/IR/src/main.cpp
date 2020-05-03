#include <Arduino.h>
#define IRSend 3
#define IRRecieve 4
#define servo 5

void pour()
{
  analogWrite(servo, 255);
}

void relax()
{
  analogWrite(servo, 0);
}

void setup()
{
  Serial.begin(9600);
  pinMode(IRSend, OUTPUT);
  pinMode(IRRecieve, INPUT);
  pinMode(servo, OUTPUT);
  digitalWrite(IRSend, HIGH);
}

void loop()
{
  digitalWrite(IRRecieve, HIGH);
  // when reciever gets a signal connects to GND so sends a 0
  // so when an obstacle comes, it doesnt send 0
  if (digitalRead(IRRecieve))
  {
    Serial.println("hand");
    pour;
    delay(1000);
    relax;
    delay(1000);
  }
  digitalWrite(IRSend, LOW);
}