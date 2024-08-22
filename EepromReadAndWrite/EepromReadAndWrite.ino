#include <Wire.h>

void setup() 
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  int value = 101;
  int address = 0;
  int data = 0;

  for (int i = 0; i < 8; i++) {
    Write(0x50, i, (value + i));
    delay(100);
  }

  for (int i = 0; i < 8; i++) {
    data = Read(0x50, i);
    Serial.print(data);
    Serial.print("\t");
  }

  Serial.println();
  delay(2000);
}

void Write(int id, unsigned int address, int value) 
{
  Wire.beginTransmission(id);
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.write(value);
  Wire.endTransmission();
}

int Read(int id, unsigned int address) 
{
  int data = 0;
  Wire.beginTransmission(id);
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.endTransmission();

  Wire.requestFrom(0x50, 1);
  if (Wire.available())
    data = Wire.read();

  return data;
}