#ifndef CONTROL_H
#define CONTROL_H

#include <stdbool.h>

typedef struct {
	unsigned long curr;
	unsigned long prev;
	unsigned long itvl;
	unsigned long (*cntr)();
} Control_t;

void attach_counter(Control_t * Control, unsigned long (*counter)())
{
	Control->cntr = counter;
}

void set_interval(Control_t * Control, unsigned long interval)
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

Control_t new_control(unsigned long (*counter)(), unsigned long interval)
{
	Control_t ret;
	ret.curr = 0;
	ret.prev = 0;
	ret.itvl = interval;
	ret.cntr = counter;
	return ret;
}

#endif
