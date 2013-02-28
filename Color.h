#ifndef _COLOR_H_
#define _COLOR_H_
#include <stdint.h>

struct Color
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};
typedef Color Colour;

static Color ConstructColor(uint8_t aR, uint8_t aG, uint8_t aB, uint8_t anA) {
	Color output = { aR, aG, aB, anA };
	return output;
}

#endif