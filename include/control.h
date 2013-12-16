#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint64_t curr;
	uint64_t prev;
	uint64_t itvl;
	uint64_t (*cntr)();
} Control_t;

void attach_counter(Control_t * Control, uint64_t (*counter)())
{
	Control->cntr = counter;
}

void set_interval(Control_t * Control, uint64_t interval)
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

Control_t new_control(uint64_t (*counter)(), uint64_t interval)
{
	Control_t ret;
	ret.curr = 0;
	ret.prev = 0;
	ret.itvl = interval;
	ret.cntr = counter;
	return ret;
}

#endif
