#ifndef STRINGIFY_H
#define STRINGIFY_H

#define PRECISION 4

#include <cstdlib>

template<typename Type>
uint8_t __fetch_size__(Type val, bool decimal)
{
	uint8_t size = 0;
	if(val < 0)
	{
		size++;
		val *= -1;
	}
	for(uint32_t test = 1000000000; test > 1; test /= 10)
	{
		if(val >= test)
		{
			val /= 10;
			size++;
		}
	}
	size = decimal ? size + PRECISION : size;
	return size;
}

template<typename Type>
char * stringify(Type val, bool decimal)
{
	char * data = (char*) malloc(__fetch_size__<Type>(val) * sizeof(char));
	if(decimal)
		sprintf(data, "%f", val);
	else
		sprintf(data, "%ld", val);
	return data;
}

#endif
