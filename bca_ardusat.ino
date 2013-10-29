#include <Wire.h>
#include <I2C_Conv.h>
#include <I2C_add.h>
#include <EEPROM.h>
#include "SAT_Geiger.h"
#include "lib/control.h"

#define CYCLE 2000

SAT_Geiger geiger;

void flush_buffer();
void log_geiger_data();

void setup()
{
	Serial.begin(1152000);
	Wire.begin();
	Control.init(CYCLE);
}

void loop()
{
	flush_buffer();
	if(Control.update())
	{
		log_geiger_data();
	}
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
