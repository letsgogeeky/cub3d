#include "../../../include/cube.h"

t_column	calculate_height(t_game *game)
{
	t_column	column;

	game->ray.wall_height = 1 / game->ray.len_to_wall * HEIGHT; //has to be len_to_plane but this is not calculated correctly yet
	column.wall_height = game->ray.wall_height;
	column.end_ceiling = (HEIGHT - column.wall_height) / 2;
	column.start_floor = column.end_ceiling + game->ray.wall_height;
	return (column);
}

void	calculate_length_to_plane(t_game *game)
{
	double		len;
	t_vector	hit;
	t_vector	dir;
	double		radian;

	len = game->ray.len_to_wall;
	hit = game->ray.hitpoint;
	dir = game->player.dir;
	radian = acos((hit.x * dir.y + hit.y * dir.x) / \
		(sqrt(hit.x * hit.x + hit.y * hit.y) * \
		sqrt(dir.x * dir.x + dir.y * dir.y)));
	// printf("radian: %f\n", (hit.x * dir.y + hit.y * dir.x) / \
		(sqrt(hit.x * hit.x + hit.y * hit.y) * \
		sqrt(dir.x * dir.x + dir.y * dir.y)));
	game->ray.len_to_plane = cos(radian) * len;
}
