#include <Wire.h>

void setup() 
{
  Wire.begin();
  Serial.begin(9600);

  char data[] = "this is data from the eeprom";
  EepromWritePage(0x50, 0, (byte *)data, sizeof(data));
  delay(100);
  Serial.println("Memory written...");
}

void loop() 
{
  int addr = 0;
  byte b = EepromReadByte(0x50, 0);

  while (b != 0) {
    Serial.print((char)b);
    addr++;
    b = EepromReadByte(0x50, addr);
  }

  Serial.println(" ");
  delay(2000);
}

void EepromWriteByte(int device_address, unsigned int eeprom_address, byte data) 
{
  int r_data = data;
  Wire.beginTransmission(device_address);
  Wire.write((int)(eeprom_address >> 8));    // MSB
  Wire.write((int)(eeprom_address & 0xFF));  // LSB
  Wire.write(r_data);
  Wire.endTransmission();
}

void EepromWritePage(int device_address, unsigned int eeprom_address_page, byte *data, byte length) 
{
  Wire.beginTransmission(device_address);
  Wire.write((int)(eeprom_address_page >> 8));    // MSB
  Wire.write((int)(eeprom_address_page & 0xFF));  // LSB
  for (byte c = 0; c < length; c++)
    Wire.write(data[c]);
  Wire.endTransmission();
}

byte EepromReadByte(int device_address, unsigned int eeprom_address) 
{
  byte r_data = 0xFF;
  Wire.beginTransmission(device_address);
  Wire.write((int)(eeprom_address >> 8));    // MSB
  Wire.write((int)(eeprom_address & 0xFF));  // LSB
  Wire.endTransmission();

  Wire.requestFrom(device_address, 1);
  if (Wire.available()) 
    r_data = Wire.read();

  return r_data;
}

void EepromReadBuffer(int device_address, unsigned int eeprom_address, byte *buffer, int length) 
{
  Wire.beginTransmission(device_address);
  Wire.write((int)(eeprom_address >> 8));    // MSB
  Wire.write((int)(eeprom_address & 0xFF));  // LSB
  Wire.endTransmission();

  Wire.requestFrom(device_address, length);
  for (int c = 0; c < length; c++) {
    if (Wire.available()) 
      buffer[c] = Wire.read();
  }
}