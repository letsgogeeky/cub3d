#include "cube.h"

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.angle.x = 0;
	ray.angle.y = 0;
	// ray.dir.x = 0;
	// ray.dir.y = 0;
	ray.side_dist.x = 0;
	ray.side_dist.y = 0;
	ray.delta_dist.x = 0;
	ray.delta_dist.y = 0;
	// ray.map.x = 0;
	// ray.map.y = 0;
	// ray.step.x = 0;
	// ray.step.y = 0;
	return (ray);
}

void	cast(t_map *map)
{
	(void)map;
}