#include <Wire.h>
#include <I2C_Conv.h>
#include <I2C_add.h>
#include <EEPROM.h>
#include "SAT_Geiger.h"
#include "SAT_AppStorage.h"
#include "lib/control/new/control.h"
#include "lib/stringify/stringify.h"

#define CYCLE 2000

SAT_Geiger Geiger;
SAT_AppStorage Storage;

void flush_buffer();
void log_geiger_data();

void setup()
{
	Wire.begin();
	init_control(millis, CYCLE);
	Storage.send("Tube,cpm,uSv/h");
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
		Storage.send(stringify<int>(i, false);
		Storage.send(",");
		Storage.send(stringify<int>(Geiger.getCPM(i), false));
		Storage.send(",");
		Storage.send(stringify<float>(Geiger.getUSPH(i), true));
		Storage.send("\n");
	}
}
