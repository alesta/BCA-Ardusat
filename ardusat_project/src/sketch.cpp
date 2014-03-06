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

#include "control.h"
#include <EEPROM.h>
#include <I2C_add.h>
#include <I2C_Conv.h>
#include <nanosat_message.h>
#include <OnboardCommLayer.h>
#include <SAT_AppStorage.h>
#include <SAT_Accel.h>
#include <SAT_Mag.h>
#include <Wire.h>
#include <stdio.h>

#define CYCLE 2000

SAT_Mag Magno;
SAT_AppStorage Storage;
SAT_Accel Accel;

Control_t MagnoControl;

void flush_buffer(void);
void log_magno_data(void);

void setup()
{
	Wire.begin();
	Magno.configMag();
	Accel.powerOn();
	
	MagnoControl = new_control(millis, CYCLE);
	// Time, Velocity x, Velocity y, Velocity z, Altitude, Magnetometer x, Magnetometer y, Magnetometer z
	Storage.send("t,vx,vy,vz,alt,magx,magy,magz");
}

void loop()
{
	flush_buffer();
	if(update(&MagnoControl))
	{
		log_magno_data();
	}
}

void flush_buffer(void)
{
	while(Wire.available())
	{
		Wire.read();
	}
}

/*
 * Logs the collected data to file.  Keep in mind that the maximum file size for a given experiment is 10kb.
 *  
 * Data points required for these measurements:
 * 1. Time
 * 2. Velocity x,y,z
 * 3. Altitude
 * 4. Magnetometer x,y,z
 */
void log_magno_data(void)
{
	char * buffer = (char*) malloc(sizeof(char) * 16);
	
	// TODO: get time measurement
	
	int x, y, z;
	Accel.readAccel(&x,&y,&z);
	snprintf(buffer, 8, "%d", x); // XYZ coords only use 8 bytes to save space
	Storage.send(buffer);
	Storage.send(",");
	snprintf(buffer, 8, "%d", y); // XYZ coords only use 8 bytes to save space
	Storage.send(buffer);
	Storage.send(",");
	snprintf(buffer, 8, "%d", z); // XYZ coords only use 8 bytes to save space
	Storage.send(buffer);
	
	// TODO: get altitude measurement
	
	Storage.send(",");
	snprintf(buffer, 8, "%d", Magno.readx()); // XYZ coords only use 8 bytes to save space
	Storage.send(buffer);
	Storage.send(",");
	snprintf(buffer, 8, "%d", Magno.ready()); // XYZ coords only use 8 bytes to save space
	Storage.send(buffer);
	Storage.send(",");
	snprintf(buffer, 8, "%d", Magno.readz()); // XYZ coords only use 8 bytes to save space
	Storage.send(buffer);
	Storage.send("\n");
	free(buffer);
}