#include "cube.h"

void	set_point(t_game *game, t_position *point, int radius)
{
	point->x = point->x * game->block_size - radius;
	point->y = point->y * game->block_size - radius;
}
