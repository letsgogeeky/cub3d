#include "cube.h"

void	move_forward(t_game *game)
{
	t_map	*map;
	t_player	*player;

	map = game->map;
	player = &game->player;
	if (map->map[(int)(player->pos.x + player->dir.x * player->walk_speed)][(int)player->pos.y] != '1')
		player->pos.x += player->dir.x * player->walk_speed;
	if (map->map[(int)player->pos.x][(int)(player->pos.y + player->dir.y * player->walk_speed)] != '1')
		player->pos.y += player->dir.y * player->walk_speed;
}

void	move_backward(t_game *game)
{
	t_map	*map;
	t_player	*player;

	map = game->map;
	player = &game->player;
	if (map->map[(int)(player->pos.x - player->dir.x * player->walk_speed)][(int)player->pos.y] != '1')
		player->pos.x -= player->dir.x * player->walk_speed;
	if (map->map[(int)player->pos.x][(int)(player->pos.y - player->dir.y * player->walk_speed)] != '1')
		player->pos.y -= player->dir.y * player->walk_speed;
}

void	turn_left(t_game *game)
{
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;

	player = &game->player;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(player->turn_speed) - player->dir.y * sin(player->turn_speed);
	player->dir.y = old_dir_x * sin(player->turn_speed) + player->dir.y * cos(player->turn_speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(player->turn_speed) - player->plane.y * sin(player->turn_speed);
	player->plane.y = old_plane_x * sin(player->turn_speed) + player->plane.y * cos(player->turn_speed);
}

void	turn_right(t_game *game)
{
	t_player	*player;
	double	old_dir_x;
	double	old_plane_x;

	player = &game->player;
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * cos(-player->turn_speed) - player->dir.y * sin(-player->turn_speed);
	player->dir.y = old_dir_x * sin(-player->turn_speed) + player->dir.y * cos(-player->turn_speed);
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * cos(-player->turn_speed) - player->plane.y * sin(-player->turn_speed);
	player->plane.y = old_plane_x * sin(-player->turn_speed) + player->plane.y * cos(-player->turn_speed);
}

void	move_left(t_game *game)
{
	t_map	*map;
	t_player	*player;

	map = game->map;
	player = &game->player;
	if (map->map[(int)(player->pos.x - player->plane.x * player->walk_speed)][(int)player->pos.y] != '1')
		player->pos.x -= player->plane.x * player->walk_speed;
	if (map->map[(int)player->pos.x][(int)(player->pos.y - player->plane.y * player->walk_speed)] != '1')
		player->pos.y -= player->plane.y * player->walk_speed;
}

void	move_right(t_game *game)
{
	t_map	*map;
	t_player	*player;

	map = game->map;
	player = &game->player;
	if (map->map[(int)(player->pos.x + player->plane.x * player->walk_speed)][(int)player->pos.y] != '1')
		player->pos.x += player->plane.x * player->walk_speed;
	if (map->map[(int)player->pos.x][(int)(player->pos.y + player->plane.y * player->walk_speed)] != '1')
		player->pos.y += player->plane.y * player->walk_speed;
}
