#include "cube.h"

t_position	get_player_position(t_map *map)
{
	t_position	position;
	int			i;
	int			j;

	i = 0;
	position.x = -1;
	position.y = -1;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (is_orientation(map->map[i][j]))
			{
				position.x = j + 0.5;
				position.y = i + 0.5;
				return (position);
			}
			j++;
		}
		i++;
	}
	return (position);
}

enum e_direction initial_orientation(t_map *map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < map->rows)
	{
		j = 0;
		while (j < map->cols)
		{
			if (is_orientation(map->map[i][j]))
				return (get_orientation(map->map[i][j]));
			j++;
		}
		i++;
	}
	return (UNKNOWN);
}
void	transform_orientation(t_player *player)
{
	if (player->init_orientation == NORTH)
	{
		player->dir.y = -1;
		player->plane.x = -0.66;
	}
	else if (player->init_orientation == SOUTH)
	{
		player->dir.y = 1;
		player->plane.x = 0.66;
	}
	else if (player->init_orientation == WEST)
	{
		player->dir.x = -1;
		player->plane.y = 0.66;
	}
	else if (player->init_orientation == EAST)
	{
		player->dir.x = 1;
		player->plane.y = -0.66;
	}
}
t_player	init_player(t_map *map)
{
	t_player	player;

	player.pos = get_player_position(map);
	player.init_orientation = initial_orientation(map);
	player.dir.x = 0;
	player.dir.y = 0;
	player.plane.x = 0;
	player.plane.y = 0;
	transform_orientation(&player);
	player.rotation_angle = 0;
	player.walk_speed = 0.08;
	player.turn_speed = 0.05;
	return (player);
}

bool	player_collision(t_game *game, t_position point, int radius)
{
	int i;
	int	j;
	double dist;
	t_position	pos_scaled;

	i = -1;
	point.x = point.x * game->block_size - radius;
	point.y = point.y * game->block_size - radius;
	while (++i < radius * 2)
	{
		j = -1;
		while (++j < radius * 2)
		{
			dist = sqrt_xy_squared((i - radius), (j - radius));
			if (dist > radius - 1 && dist < radius + 1)
			{
				pos_scaled.x = (point.x + i) / game->block_size;
				pos_scaled.y = (point.y + j) / game->block_size;
				if (game->map->map[(int)pos_scaled.x][(int)pos_scaled.y] == WALL || \
					(game->map->map[(int)pos_scaled.x][(int)pos_scaled.y] == DOOR && \
					!door_is_open(game, (int)pos_scaled.x, (int)pos_scaled.y)))
					return (true);
			}
		}
	}
	return (false);
}

bool	player_inside_door(t_game *game, t_position point, int radius)
{
	int i;
	int	j;
	double dist;
	t_position	pos_scaled;

	i = -1;
	point.x = point.x * game->block_size - radius;
	point.y = point.y * game->block_size - radius;
	while (++i < radius * 2)
	{
		j = -1;
		while (++j < radius * 2)
		{
			dist = sqrt_xy_squared((i - radius), (j - radius));
			if (dist > radius - 1 && dist < radius + 1)
			{
				pos_scaled.x = (point.x + i) / game->block_size;
				pos_scaled.y = (point.y + j) / game->block_size;
				if (game->map->map[(int)pos_scaled.x][(int)pos_scaled.y] == DOOR)
					return (true);
			}
		}
	}
	return (false);
}
