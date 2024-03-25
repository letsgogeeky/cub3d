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
	if (player_collision(game, (t_position){next_y, next_x}, \
		game->minimap->p_radius))
		return ;
	if (map->map[(int)player->pos.y][(int)next_x] != WALL)
		player->pos.x = next_x;
	if (map->map[(int)next_y][(int)player->pos.x] != WALL)
		player->pos.y = next_y;
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
	if (player_collision(game, (t_position){next_y, next_x}, \
		game->minimap->p_radius))
		return ;
	if (map->map[(int)player->pos.y][(int)next_x] != WALL)
		player->pos.x = next_x;
	if (map->map[(int)next_y][(int)player->pos.x] != WALL)
		player->pos.y = next_y;
}

void	rotate(t_game *game, bool clockwise)
{
	t_player	*player;
	int			rot_dir;
	double		speed_dir;

	rot_dir = 1;
	if (clockwise)
		rot_dir = -1;
	player = &game->player;
	speed_dir = player->turn_speed * rot_dir;
	player->dir = rotate_vector(player->dir, speed_dir);
	player->plane = rotate_vector(player->plane, speed_dir);
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
	if (player_collision(game, (t_position){next_y, next_x}, \
		game->minimap->p_radius))
		return ;
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
	if (player_collision(game, (t_position){next_y, next_x}, \
		game->minimap->p_radius))
		return ;
	if (map->map[(int)player->pos.y][(int)next_x] != WALL)
		player->pos.x = next_x;
	if (map->map[(int)next_y][(int)player->pos.x] != WALL)
		player->pos.y = next_y;
}
