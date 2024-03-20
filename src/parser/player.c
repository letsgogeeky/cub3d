#include "cube.h"

char	*direction_to_str(enum e_direction direction)
{
	if (direction == NORTH)
		return ("NORTH");
	if (direction == SOUTH)
		return ("SOUTH");
	if (direction == WEST)
		return ("WEST");
	if (direction == EAST)
		return ("EAST");
	return ("INVALID");
}

enum e_direction	get_orientation(char c)
{
	if (c == 'N')
		return (NORTH);
	if (c == 'S')
		return (SOUTH);
	if (c == 'W')
		return (WEST);
	if (c == 'E')
		return (EAST);
	return (0);
}

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
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				position.x = j;
				position.y = i;
				// position.direction = get_direction(map->map[i][j]);
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
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
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
	ft_printf("Initial orientation: %s\n", direction_to_str(player.init_orientation));
	player.dir.x = 0;
	player.dir.y = 0;
	player.plane.x = 0;
	player.plane.y = 0;
	transform_orientation(&player);
	player.rotation_angle = 0;
	player.walk_speed = 0.1;
	player.turn_speed = 0.07;
	return (player);
}

void	log_player_position(t_map *map)
{
	t_position	position;

	position = get_player_position(map);
	ft_printf("Player position: X: %d, Y: %d, Direction: %s\n", \
		position.x, position.y, direction_to_str(1));
}
