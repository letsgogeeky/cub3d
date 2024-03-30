#include "cube.h"

char	*direction_to_str(enum e_dir direction)
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

bool	is_orientation(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

enum e_dir	get_orientation(char c)
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

void	log_player_position(t_map *map)
{
	t_position	position;

	position = get_player_position(map);
	printf("Player position: X: %f, Y: %f, Direction: %s\n", \
		position.x, position.y, direction_to_str(1));
}
