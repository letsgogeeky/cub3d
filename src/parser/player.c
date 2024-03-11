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

enum e_direction	get_direction(char c)
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

void	log_player_position(t_map *map)
{
	t_position	position;

	position = get_player_position(map);
	ft_printf("Player position: X: %d, Y: %d, Direction: %s\n", \
		position.x, position.y, direction_to_str(1));
}
