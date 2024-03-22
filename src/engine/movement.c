#include "cube.h"

bool	check_hitbox_collision(t_game *game, t_position point, int radius)
{
	int i, j;
	double dist;
	t_position	pos_scaled;

	i = 0;
	point.x = point.x * game->block_size + (game->block_size / 4);
	point.y = point.y * game->block_size + (game->block_size / 4);
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			dist = sqrt((i - radius) * (i - radius) + (j - radius) * (j - radius));
			if (dist > radius - 1 && dist < radius + 1)
			{
				pos_scaled.x = (point.x + i) / game->block_size;
				pos_scaled.y = (point.y + j) / game->block_size;
				if (game->map->map[(int)pos_scaled.x][(int)pos_scaled.y] == WALL)
					return (true);
			}
			j++;
		}
		i++;
	}
	return (false);
}

void	move_forward(t_game *game)
{
	t_map		*map;
	t_player	*player;
	double		next_x;
	double		next_y;
	// bool		hit;

	map = game->map;
	player = &game->player;
	next_x = player->pos.x + player->dir.x * player->walk_speed;
	next_y = player->pos.y + player->dir.y * player->walk_speed;
	ft_printf("next_x: %f, next_y: %f\n", next_x, next_y);
	// hit = check_hitbox_collision(game, (t_position){next_y , next_x}, game->minimap->p_radius);
	// if (hit)
	// 	return ;
	// if (player->dir.x >= 0 && player->dir.y >= 0 && map->map[(int)ceilf(next_y)][(int)ceilf(next_x - 0.1)] == WALL)
	// 	return ;
	// if (player->dir.x <= 0 && player->dir.y <= 0 && map->map[(int)floorf(next_y)][(int)floorf(next_x)] == WALL)
	// 	return ;
	// if (player->dir.x >= 0 && player->dir.y <= 0 && map->map[(int)floorf(next_y)][(int)ceilf(next_x)] == WALL)
	// 	return ;
	// if (player->dir.x <= 0 && player->dir.y >= 0 && map->map[(int)ceilf(next_y)][(int)floorf(next_x)] == WALL)
	// 	return ;
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
	// bool		hit;

	map = game->map;
	player = &game->player;
	next_x = player->pos.x - player->dir.x * player->walk_speed;
	next_y = player->pos.y - player->dir.y * player->walk_speed;
	// hit = check_hitbox_collision(game, (t_position){next_y , next_x}, game->minimap->p_radius);
	// if (hit)
	// 	return ;
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
	// bool		hit;

	map = game->map;
	player = &game->player;
	next_x = player->pos.x + player->plane.x * player->walk_speed;
	next_y = player->pos.y + player->plane.y * player->walk_speed;
	// hit = check_hitbox_collision(game, (t_position){next_y , next_x}, game->minimap->p_radius);
	// if (hit)
	// 	return ;
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
	// bool		hit;

	map = game->map;
	player = &game->player;
	next_x = player->pos.x - player->plane.x * player->walk_speed;
	next_y = player->pos.y - player->plane.y * player->walk_speed;
	// hit = check_hitbox_collision(game, (t_position){next_y , next_x}, game->minimap->p_radius);
	// if (hit)
	// 	return ;
	if (map->map[(int)player->pos.y][(int)next_x] != WALL)
		player->pos.x = next_x;
	if (map->map[(int)next_y][(int)player->pos.x] != WALL)
		player->pos.y = next_y;
}
