#ifndef CONTROL_H
#define CONTROL_H

#include <inttypes.h>
#include "Arduino.h"

typedef enum {
	CURRENT,
	PREVIOUS,
	INTERVAL,
} control_val_t;

typedef struct Control {
	uint32_t curr;
	uint32_t prev;
	uint32_t itvl;

	void init();
	void init(uint32_t itvl);
	void init(uint32_t curr, uint32_t prev, uint32_t itvl);
	void change(uint32_t val, control_val_t tar);
	void update();
} Control;

#endif
