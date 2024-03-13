#include "cube.h"

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

t_player	init_player(t_map *map)
{
	t_player	player;

	player.pos = get_player_position(map);
	player.initial_orientation = initial_orientation(map);
	ft_printf("Initial orientation: %s\n", direction_to_str(player.initial_orientation));
	player.dir.x = 0;
	player.dir.y = 0;
	player.plane.x = 0;
	player.plane.y = 0;
	if (player.initial_orientation == NORTH)
	{
		player.dir.x = -1;
		player.plane.y = 0.66;
	}
	else if (player.initial_orientation == SOUTH)
	{
		player.dir.x = 1;
		player.plane.y = -0.66;
	}
	else if (player.initial_orientation == WEST)
	{
		player.dir.y = -1;
		player.plane.x = -0.66;
	}
	else if (player.initial_orientation == EAST)
	{
		player.dir.y = 1;
		player.plane.x = 0.66;
	}
	player.rotation_angle = 0;
	player.walk_speed = 0.1;
	player.turn_speed = 0.1;
	return (player);
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
				return (position);
			}
			j++;
		}
		i++;
	}
	return (position);
}

void	log_player_position(t_map *map)
{
	t_position	position;

	position = get_player_position(map);
	ft_printf("Player position: X: %d, Y: %d, Direction: %s\n", \
		position.x, position.y, direction_to_str(1));
}

void	show_player(t_game *game)
{
	int	x;
	int	y;
	t_player *player;

	player = &game->data->player;

	ft_printf("Direction: %f, %f\n", player->dir.x, player->dir.y);
	ft_printf("Position: %f, %f\n", player->pos.x, player->pos.y);
	x = player->pos.x * game->block_size;
	y = player->pos.y * game->block_size;
	ft_printf("x: %d, y: %d\n", x, y);
	fill_block(game, game->block_size, x, y, 0x00FFFFFF);
	// visualize_2d_ray(game, 0x000000FF);
}
