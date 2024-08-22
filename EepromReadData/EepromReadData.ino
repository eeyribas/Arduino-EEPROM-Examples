#include <Wire.h>

void setup() 
{
  Wire.begin();
  Serial.begin(9600);

  int data = 0;
  for (int i = 0; i < 32765; i++) {
    data = Read(0x50, i);
    Serial.print(i);
    Serial.print(" : ");
    Serial.println(data);
  }
}

void loop() 
{

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