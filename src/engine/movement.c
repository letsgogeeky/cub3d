#include "cube.h"

void	move_forward(t_game *game)
{
	t_map		*map;
	t_player	*player;
	double		next_x;
	double		next_y;

	map = game->map;
	player = &game->player;
	next_x = player->pos.x + player->dir.x * player->walk_speed;
	next_y = player->pos.y + player->dir.y * player->walk_speed;
	if (player->dir.x < 0)
	{
		ft_printf("rounding next_x: %f\n", round(next_x));
		if (map->map[(int)player->pos.y][(int)round(next_x)] != WALL)
			player->pos.x = next_x;
	}
	else
	{
		ft_printf("ceiling next_x: %f\n", ceilf(next_x));
		if (map->map[(int)player->pos.y][(int)ceilf(next_x)] != WALL)
			player->pos.x = next_x;
	}
	if (player->dir.y < 0)
	{
		ft_printf("round next_y: %f\n", round(next_y));
		if (map->map[(int)round(next_y)][(int)player->pos.x] != WALL)
			player->pos.y = next_y;
	}
	else
	{
		ft_printf("ceiling next_y: %f\n", ceilf(next_y));
		if (map->map[(int)ceilf(next_y)][(int)player->pos.x] != WALL)
			player->pos.y = next_y;
	}
}

void	move_backward(t_game *game)
{
	t_map		*map;
	t_player	*player;
	double		next_x;
	double		next_y;

	map = game->map;
	player = &game->player;
	next_x = player->pos.x - player->dir.x * player->walk_speed;
	next_y = player->pos.y - player->dir.y * player->walk_speed;
	if (map->map[(int)player->pos.y][(int)next_x] != WALL)
		player->pos.x = next_x;
	if (map->map[(int)next_y][(int)player->pos.x] != WALL)
		player->pos.y = next_y;
}

void	rotate(t_game *game, bool clockwise)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;
	int			rot_dir;
	double		speed_dir;

	rot_dir = 1;
	if (clockwise)
		rot_dir = -1;
	player = &game->player;
	speed_dir = player->turn_speed * rot_dir;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(speed_dir) - player->dir.y * sin(speed_dir);
	player->dir.y = old_dir_x * sin(speed_dir) + player->dir.y * cos(speed_dir);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(speed_dir) - player->plane.y * sin(speed_dir);
	player->plane.y = old_plane_x * sin(speed_dir) + player->plane.y * cos(speed_dir);
}

void	move_left(t_game *game)
{
	t_map		*map;
	t_player	*player;
	double		next_x;
	double		next_y;

	map = game->map;
	player = &game->player;
	next_x = player->pos.x + player->plane.x * player->walk_speed;
	next_y = player->pos.y + player->plane.y * player->walk_speed;
	if (map->map[(int)player->pos.y][(int)next_x] != WALL)
		player->pos.x = next_x;
	if (map->map[(int)next_y][(int)player->pos.x] != WALL)
		player->pos.y = next_y;
}

void	move_right(t_game *game)
{
		t_map		*map;
	t_player	*player;
	double		next_x;
	double		next_y;

	map = game->map;
	player = &game->player;
	next_x = player->pos.x - player->plane.x * player->walk_speed;
	next_y = player->pos.y - player->plane.y * player->walk_speed;
	if (map->map[(int)player->pos.y][(int)next_x] != WALL)
		player->pos.x = next_x;
	if (map->map[(int)next_y][(int)player->pos.x] != WALL)
		player->pos.y = next_y;
}
