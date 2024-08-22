#include <Wire.h>

int eeprom_address = 100;

void setup() 
{
  Wire.begin();
  Serial.begin(9600);

  Write(0x50, 0, 2);
  delay(100);
  Write(0x50, 1, 3);
  delay(100);
  Write(0x50, 2, 4);
  delay(100);
  Write(0x50, 3, 5);
  delay(100);

  Serial.println("Data written...");
}

void loop() 
{
  int data = 1;
  for (int i = 0; i < 4; i++) {
    data = Read(0x50, i);
    Serial.print(data);
    Serial.print("\t");
  }
  Serial.println();
  delay(2000);

  int last_address = FindEmptyAddress();
  Serial.print("Last Address = ");
  Serial.print(last_address);
  Serial.println();
  delay(2000);
}

void Write(int id, int address, int value) 
{
  Wire.beginTransmission(id);
  Wire.write((int)(address >> 8));
  Wire.write((int)(address & 0xFF));
  Wire.write(value);
  Wire.endTransmission();
}

int Read(int id, int address) 
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

int FindEmptyAddress() 
{
  int count = 0;
  int data = 0;
  for (count = 0; count < eeprom_address; count++) {
    data = Read(0x50, count);
    if (data == 3 || data == 4)
      break;
  }

  return count;
}