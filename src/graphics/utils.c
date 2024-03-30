#include "cube.h"

int	colorcode(int red, int green, int blue, int alpha)
{
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}
