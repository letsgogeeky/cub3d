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

bool	is_orientation(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
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

void	log_player_position(t_map *map)
{
	t_position	position;

	position = get_player_position(map);
	printf("Player position: X: %f, Y: %f, Direction: %s\n", \
		position.x, position.y, direction_to_str(1));
}
