#include <Wire.h>

void setup() 
{
  Wire.begin();
  Serial.begin(9600);

  for (int i = 0; i < 10500; i++) {
    Write(0x50, i, 90);
    delay(10);
  }
  Serial.println("Loading...");
}

void loop() 
{

}

void Write(int id, unsigned int address, int value) 
{
  Wire.beginTransmission(id);
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.write(value);
  Wire.endTransmission();
}