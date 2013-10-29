#include <Wire.h>
#include <I2C_Conv.h>
#include <I2C_add.h>
#include <EEPROM.h>
#include "SAT_Geiger.h"

#define CYCLE 2000

SAT_Geiger geiger;

uint32_t prev = 0;
uint32_t time = 0;


void flush_buffer();
void log_geiger_data();

void setup()
{
  Serial.begin(1152000);
  Wire.begin();
}

void loop()
{
  flush_buffer();
  
}

void flush_buffer()
{
  while(Wire.available())
  {
    Wire.read();
  }
}

void log_geiger_data()
{
  
}
