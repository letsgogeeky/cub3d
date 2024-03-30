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
		game->ray.len_to_wall = vector_length(&game->ray.side_dist_x);
		set_wall_direction(&game->ray.side_dist_x, 1, game);
	}
	else
	{
		hitpoint->x = game->player.pos.x + game->ray.side_dist_y.x;
		hitpoint->y = game->player.pos.y + game->ray.side_dist_y.y;
		game->ray.len_to_wall = vector_length(&game->ray.side_dist_y);
		set_wall_direction(&game->ray.side_dist_y, 0, game);
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

	map = game->map->map;
	i = (int)(hitpoint.x + 0.00001 * game->ray.angle.x);
	j = (int)(hitpoint.y + 0.00001 * game->ray.angle.y);
	if (j >= 0 && i >= 0 && j < game->map->rows && i < game->map->cols && \
		map[j][i] && (map[j][i] == WALL || \
		(map[j][i] == DOOR && !door_is_open(game, j, i))))
	{
		game->ray.hitpoint.x = hitpoint.x;
		game->ray.hitpoint.y = hitpoint.y;
		return (1);
	}
	return (0);
}
