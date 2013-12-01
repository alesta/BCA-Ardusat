#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint32_t curr;
	uint32_t prev;
	uint32_t itvl;
	uint32_t (*cntr)();
} Control_t;

void attach_counter(Control_t * Control, uint32_t (*counter)())
{
	Control->cntr = counter;
}

void set_interval(Control_t * Control, uint32_t interval)
{
	Control->itvl = interval;
}

bool update(Control_t * Control)
{
	Control->curr = Control->cntr();
	if(Control->curr - Control->prev >= Control->itvl)
	{
		Control->prev = Control->curr;
		return 1;
	}
	return 0;
}

Control_t new_control(uint32_t (*counter)(), uint32_t interval)
{
	Control_t ret;
	ret.curr = 0;
	ret.prev = 0;
	ret.itvl = interval;
	ret.cntr = counter;
	return ret;
}

#endif
