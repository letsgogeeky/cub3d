#include "cube.h"

int	doors_count(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (j < map->rows)
	{
		while (i < map->cols)
		{
			if (map->map[j][i] == DOOR)
				count++;
			i++;
		}
		i = 0;
		j++;
	}
	return (count);
}

bool	door_is_open(t_game *game, int x, int y)
{
	int	i;
	t_door	*doors;

	i = 0;
	doors = game->map->doors;
	while (i < game->map->doors_count)
	{
		if (doors[i].pos.x == x && doors[i].pos.y == y)
			return (doors[i].is_open);
		i++;
	}
	return (false);
}

void	door_open_close(t_game *game, int x, int y)
{
	int	i;
	t_door	*doors;

	i = 0;
	doors = game->map->doors;
	while (i < game->map->doors_count)
	{
		if (doors[i].pos.x == x && doors[i].pos.y == y)
			doors[i].is_open = !doors[i].is_open;
		i++;
	}
}

void	door_control(t_game *game)
{
	int	next_x;
	int	next_y;
	t_player	*player;
	t_map		*map;

	map = game->map;
	player = &game->player;
	if (player_inside_door(game, (t_position){player->pos.y, player->pos.x}, \
		game->minimap->p_radius))
	{
		printf("Cannot open/close door, player is too close. their toes will be hurt!\n");
		return ;
	}
	next_x = player->pos.x + player->dir.x * (player->walk_speed * 5);
	next_y = player->pos.y + player->dir.y * (player->walk_speed * 5);
	if (map->map[(int)player->pos.y][(int)next_x] == DOOR)
		door_open_close(game, (int)player->pos.y, (int)next_x);
	else if (map->map[(int)next_y][(int)player->pos.x] == DOOR)
		door_open_close(game, (int)next_y, (int)player->pos.x);
}


