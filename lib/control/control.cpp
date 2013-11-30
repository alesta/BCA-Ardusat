#include <stdint.h>
#include "Arduino.h"
#include "control.h"

void Control::init()
{
	this.curr = 0;
	this.prev = 0;
	this.itvl = 0;
}

void Control::init(uint32_t itvl)
{
	this.curr = 0;
	this.prev = 0;
	this.itvl = itvl;
}

void Control::init(uint32_t curr, uint32_t prev, uint32_t itvl)
{
	this.curr = curr;
	this.prev = prev;
	this.itvl = itvl;
}

void Control::change(uint32_t val, uint32_t control_val_t tar)
{
	switch(tar)
	{
		case CURRENT:
			this.curr = val;
			break;
		case PREVIOUS:
			this.prev = val;
			break;
		case INTERVAL:
			this.itvl = val;
			break;
	}
}

bool Control::update()
{
	this.curr = millis();
	if(this.curr - this.prev >= this.itvl)
	{
		this.prev = this.curr;
		return true;
	}
	return false;
}
