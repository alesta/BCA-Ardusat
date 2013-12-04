/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Wire.h>
#include <I2C_Conv.h>
#include <I2C_add.h>
#include <EEPROM.h>
#include "SAT_Geiger.h"
#include "SAT_AppStorage.h"
#include "lib/control/newer/control-v2.h"
#include "lib/stringify/stringify.h"

#define CYCLE 2000

SAT_Geiger Geiger;
SAT_AppStorage Storage;

Control_t GeigerControl;

void flush_buffer();
void log_geiger_data();

void setup()
{
	Wire.begin();
	GeigerControl = new_control(millis, CYCLE);
	Storage.send("Tube,cpm,uSv/h");
}

void loop()
{
	flush_buffer();
	if(update(&GeigerControl))
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
