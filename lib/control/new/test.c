/*
 * test.c
 * 
 * Copyright 2013 Alexander Stangl <alesta@bergen.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "control.h"

static uint32_t time;

uint32_t my_counter()
{
	return time++;
}

int main(int argc, char **argv)
{
	init_control(my_counter, 1000);
	while(1)
	{
		if(Control.update())
		{
			printf("Time at execution is %d.\n", Control.prev);
			break;
		}
	}
	printf("This should be printed at the end.\n");
	return 0;
}

