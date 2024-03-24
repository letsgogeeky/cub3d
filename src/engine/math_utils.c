#include "cube.h"

double	sqrt_xy_squared(double x, double y)
{
	return (sqrt(x * x + y * y));
}

t_vector	rotate_vector(t_vector vec, double angle)
{
	t_vector	new;

	new.x = vec.x * cos(angle) - vec.y * sin(angle);
	new.y = vec.x * sin(angle) + vec.y * cos(angle);
	return (new);
}
