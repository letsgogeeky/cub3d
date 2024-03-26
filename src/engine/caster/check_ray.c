#include "../../../include/cube.h"

int	check_first_wall(t_game *game, t_vector factor, t_position *hitpoint)
{
	game->ray.side_dist_x.x = factor.x * game->ray.step_for_plus_x.x;
	game->ray.side_dist_x.y = factor.x * game->ray.step_for_plus_x.y;
	game->ray.side_dist_y.x = factor.y * game->ray.step_for_plus_y.x;
	game->ray.side_dist_y.y = factor.y * game->ray.step_for_plus_y.y;
	if (vector_length(&game->ray.side_dist_x) < \
		vector_length(&game->ray.side_dist_y))
	{
		hitpoint->x = game->player.pos.x + game->ray.side_dist_x.x;
		hitpoint->y = game->player.pos.y + game->ray.side_dist_x.y;
		// if (hitpoint->x > 0 && hitpoint->y > 0)
		// 	add_one_step(&game->ray.side_dist_x, &game->ray.step_for_plus_x);
	}
	else
	{
		hitpoint->x = game->player.pos.x + game->ray.side_dist_y.x;
		hitpoint->y = game->player.pos.y + game->ray.side_dist_y.y;
		// if (hitpoint->x > 0 && hitpoint->y > 0)
		// 	add_one_step(&game->ray.side_dist_y, &game->ray.step_for_plus_y);
	}
	if (check_hit(game, (*hitpoint)) == 1)
		return (1);
	return (0);
}

int	check_hit(t_game *game, t_position hitpoint)
{
	char	**map;
	int		i;
	int		j;
	// int		test;

	map = game->map->map;
	i = (int)(hitpoint.x + 0.00001 * game->ray.angle.x);
	j = (int)(hitpoint.y + 0.00001 * game->ray.angle.y);
	// printf("check x %f -> %i\n", hitpoint.x, i);
	// printf("check y %f -> %i\n", hitpoint.y, j);
	// t_vector a, b;
	// a.x = (i + 0) * game->block_size;
	// a.y = (j + 0) * game->block_size;
	// b.x = (i + 1) * game->block_size;
	// b.y = (j + 1) * game->block_size;
	// draw_line(game, a, b, 0x00FF00FF);
	// a.y = (j + 1) * game->block_size;
	// b.y = (j + 0) * game->block_size;
	// draw_line(game, a, b, 0x00FF00FF);
	// a.x = (hitpoint.x) * game->block_size;
	// a.y = (hitpoint.y) * game->block_size + 10;
	// b.x = (hitpoint.x) * game->block_size;
	// b.y = (hitpoint.y) * game->block_size - 10;
	// draw_line(game, a, b, 0xFF0000FF);
	// a.x = (hitpoint.x) * game->block_size + 10;
	// a.y = (hitpoint.y) * game->block_size;
	// b.x = (hitpoint.x) * game->block_size - 10;
	// b.y = (hitpoint.y) * game->block_size;
	// draw_line(game, a, b, 0x0000FFFF);

	// test = ft_strncmp(&map[j][i], "1", 1);
	if (j >= 0 && i >= 0 && j < game->map->rows && i < game->map->cols && \
    map[j][i] && (map[j][i] == WALL || \
		(map[j][i] == DOOR && !door_is_open(game, j, i))))
		return (1);
	return (0);
}