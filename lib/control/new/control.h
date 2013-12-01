#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include <stdbool.h>

void __attach_counter__(uint32_t (*counter)());
void __set_interval__(uint32_t interval);
void __init__(uint32_t (*counter)(), uint32_t interval);
bool __update__();

struct {
	uint32_t curr;
	uint32_t prev;
	uint32_t itvl;
	uint32_t (*cntr)();
	void (*attach_counter)(uint32_t (*counter)());
	void (*set_interval)(uint32_t interval);
	bool (*update)();
} Control;

void __attach_counter__(uint32_t (*counter)())
{
	Control.cntr = counter;
}

void __set_interval__(uint32_t interval)
{
	Control.itvl = interval;
}

bool __update__()
{
	Control.curr = Control.cntr();
	if(Control.curr - Control.prev >= Control.itvl)
	{
		Control.prev = Control.curr;
		return 1;
	}
	return 0;
}

void init_control(uint32_t (*counter)(), uint32_t interval)
{
	Control.curr = 0;
	Control.prev = 0;
	Control.itvl = interval;
	Control.cntr = counter;
	Control.attach_counter = __attach_counter__;
	Control.set_interval = __set_interval__;
	Control.update = __update__;
}

#endif
