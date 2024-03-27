#include "../../../include/cube.h"

t_column	calculate_height(t_game *game)
{
	t_column	column;

	game->ray.wall_height = 1 / game->ray.len_to_wall * HEIGHT; //has to be len_to_plane but this is not calculated correctly yet (see below)
	column.wall_height = game->ray.wall_height;
	if (column.wall_height >= HEIGHT)
		column.wall_height = HEIGHT - 1;
	column.end_ceiling = (HEIGHT - column.wall_height) / 2;
	if (column.end_ceiling < 0)
		column.end_ceiling = 0;
	column.start_floor = column.end_ceiling + game->ray.wall_height;
	if (column.start_floor >= HEIGHT)
		column.start_floor = HEIGHT - 1;
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
	//	(sqrt(hit.x * hit.x + hit.y * hit.y) * \
	//	sqrt(dir.x * dir.x + dir.y * dir.y)));

	game->ray.len_to_plane = cos(radian) * len;
	// if (vector_length(&game->ray.side_dist_x) < \
	// 		vector_length(&game->ray.side_dist_y))
	// 	game->ray.len_to_plane = len - game->ray.step_for_plus_x.x;
	// else
	// 	game->ray.len_to_plane = len - game->ray.step_for_plus_y.y;
}
