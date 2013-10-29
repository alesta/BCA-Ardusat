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
	Serial.println("Tube, cpm, uSv/h");
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
	for(int i = 1; i < 2; i++)
	{
		Serial.print(i);
		Serial.print(",");
		Serial.print(geiger.getCPM(i));
		Serial.print(",");
		Serial.print(geiger.getUSPH(i), 4);
		Serial.print("\n");
	}
}
