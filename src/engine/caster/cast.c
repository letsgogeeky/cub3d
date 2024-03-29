#include "../../../include/cube.h"

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.dir.x = 0;
	ray.dir.y = 0;
	ray.angle.x = 0;
	ray.angle.y = 0;
	ray.step_for_plus_x.x = 0;
	ray.step_for_plus_x.y = 0;
	ray.step_for_plus_y.x = 0;
	ray.step_for_plus_y.y = 0;
	ray.hitpoint.x = 0;
	ray.hitpoint.y = 0;
	ray.side_dist_x.x = 0;
	ray.side_dist_x.y = 0;
	ray.side_dist_y.x = 0;
	ray.side_dist_y.y = 0;
	ray.delta_dist.x = 0;
	ray.delta_dist.y = 0;
	ray.map.x = 0;
	ray.map.y = 0;
	ray.len_to_wall = 0;
	ray.wall_height = 0;
	return (ray);
}

// <<<<<<< HEAD

// =======
// void	draw_line(t_game *game, t_vector start, t_vector end, int color)
// {
// 	double	x;
// 	double	y;
// 	double	dx;
// 	double	dy;
// 	double	steps;
// 	double	i;

// 	dx = end.x - start.x;
// 	dy = end.y - start.y;
// 	steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
// 	dx /= steps;
// 	dy /= steps;
// 	x = start.x;
// 	y = start.y;
// 	i = 0;
// 	while (i <= steps && x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
// 	{
// 		mlx_put_pixel(game->minimap->image, x, y, color);
// 		x += dx;
// 		y += dy;
// 		i++;
// 	}
// }

// t_vector	distance_to_wall(t_game *game)
// {
// 	t_vector	distance;
// 	int x;
// 	int y;

// 	distance.x = 0;
// 	distance.y = 0;
// 	x = (int)(game->player.pos.y + distance.y);
// 	y = (int)(game->player.pos.x + distance.x);
// 	while (game->map->map[x][y] && game->map->map[x][y] != WALL)
// 	{
// 		distance.x++;
// 		distance.y++;
// 		x = (int)(game->player.pos.y + distance.y);
// 		y = (int)(game->player.pos.x + distance.x);
// 	}
// 	return (distance);

// }

// void	visualize_2d_ray(t_game *game, int color)
// {
// 	t_vector	start;
// 	t_vector	end;
// 	int		block_size;
// 	int 	i;
// 	float dir_scalar;

// 	block_size = game->block_size;
// 	start.x = game->player.pos.x * block_size + block_size / 2;
// 	start.y = game->player.pos.y * block_size + block_size / 2;
// 	dir_scalar = 1;
// 	i = 0;
// 	while (i <= game->minimap->arrows_count)
// 	{
// 		game->ray.angle.x = game->player.dir.x + game->player.plane.x * dir_scalar;
// 		game->ray.angle.y = game->player.dir.y + game->player.plane.y * dir_scalar;
// 		end.x = (game->ray.angle.x * block_size) + start.x;
// 		end.y = (game->ray.angle.y * block_size) + start.y;
// 		draw_line(game, start, end, color);
// 		dir_scalar -= (2.0 / game->minimap->arrows_count);
// 		i++;
// 	}
// }

// void	compute_pixel_column(t_game *game, int x)
// {
// 	double	wall_hit;
// 	t_vector	wall;
// 	int		wall_height;
// 	int	y;

// 	wall_height = (int)(HEIGHT / game->ray.length);
// 	wall.x = (-wall_height / 2 + HEIGHT / 2);
// 	if (wall.x < 0)
// 		wall.x = 0;
// 	wall.y = (wall_height / 2 + HEIGHT / 2);
// 	if (wall.y >= HEIGHT)
// 		wall.y = HEIGHT - 1;
// 	if (game->ray.side == 0)
// 		wall_hit = game->player.pos.y + game->ray.length * game->ray.angle.y;
// 	else
// 		wall_hit = game->player.pos.x + game->ray.length * game->ray.angle.x;
// 	wall_hit -= floor(wall_hit);

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		if (y < wall.x)
// 			mlx_put_pixel(game->image, x, y, 0x00FF0000);
// 		else if (y > wall.x && y < wall.y)
// 			mlx_put_pixel(game->image, x, y, 0x00FFFFFF);
// 		else
// 			mlx_put_pixel(game->image, x, y, 0x000000FF);
// 		y++;
	
// 	}
// }


// void	do_raycast(t_game *game)
// {
// 	double	column_x;
// 	int		x;

// >>>>>>> 52d00aee5eb54b771c248c63de3b839067403922
void	visualize_2d_ray(t_game *game, int color)
{
	// int			block_size;
	int			x;

	// block_size = game->block_size;
	x = 0;
	while (x < AMOUNT_RAYS_2D_FOV)
	{
		set_angle(game, x);
		set_steps(game);
		calculate_hitpoint(game);
		draw_ray(game, color);
		x++;
	}
	return ;
}

// void	compute_pixel_column(t_game *game, int x)
// {
// 	double	wall_hit;
// 	t_vector	wall;
// 	int		wall_height;
// 	int	y;

// 	wall_height = (int)(HEIGHT / game->ray.length);
// 	wall.x = (-wall_height / 2 + HEIGHT / 2);
// 	if (wall.x < 0)
// 		wall.x = 0;
// 	wall.y = (wall_height / 2 + HEIGHT / 2);
// 	if (wall.y >= HEIGHT)
// 		wall.y = HEIGHT - 1;
// 	if (game->ray.side == 0)
// 		wall_hit = game->player.pos.y + game->ray.length * game->ray.angle.y;
// 	else
// 		wall_hit = game->player.pos.x + game->ray.length * game->ray.angle.x;
// 	wall_hit -= floor(wall_hit);

// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		if (y < wall.x)
// 			mlx_put_pixel(game->image, x, y, 0x00FF0000);
// 		else if (y > wall.x && y < wall.y)
// 			mlx_put_pixel(game->image, x, y, 0x00FFFFFF);
// 		else
// 			mlx_put_pixel(game->image, x, y, 0x000000FF);
// 		y++;
// 	}
// }

// void	do_raycast(t_game *game)
// {
// 	double	column_x;
// 	int		x;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		// calculate ray position and direction
// 		column_x = 2 * x / (double)WIDTH - 1;
// 		game->ray.angle.x = game->player.dir.x + game->player.plane.x * column_x;
// 		game->ray.angle.y = game->player.dir.y + game->player.plane.y * column_x;
// 		game->ray.delta_dist.x = fabs(1 / game->ray.angle.x);
// 		// if (game->ray.angle.x == 0)
// 		// 	game->ray.delta_dist.x = INFINITY;
// 		game->ray.delta_dist.y = fabs(1 / game->ray.angle.y);
// 		// if (game->ray.angle.y == 0)
// 		// 	game->ray.delta_dist.y = INFINITY;
// 		game->ray.map.x = (int)game->player.pos.x;
// 		game->ray.map.y = (int)game->player.pos.y;
// 		// calculate step and initial side_dist
// 		game->ray.side_dist.x = game->ray.delta_dist.x;
// 		game->ray.side_dist.y = game->ray.delta_dist.y;
// 		if (game->ray.angle.x < 0)
// 			game->ray.step.x = -1;
// 		else
// 			game->ray.step.x = 1;
// 		if (game->ray.angle.y < 0)
// 			game->ray.step.y = -1;
// 		else
// 			game->ray.step.y = 1;
// 		bool hit = false;
// 		while (!hit)
// 		{
// 			if (game->ray.side_dist.x < game->ray.side_dist.y)
// 			{
// 				game->ray.side_dist.x += game->ray.delta_dist.x;
// 				game->ray.map.x += game->ray.step.x;
// 				game->ray.side = 0;
// 			}
// 			else
// 			{
// 				game->ray.side_dist.y += game->ray.delta_dist.y;
// 				game->ray.map.y += game->ray.step.y;
// 				game->ray.side = 1;
// 			}
// 			int map_x = (int)game->ray.map.x;
// 			int map_y = (int)game->ray.map.y;
// 			if (map_x < 0 || map_y < 0 || map_x >= game->map->rows || map_y >= game->map->cols)
// 				break;
// 			if (game->map->map[map_x][map_y] && game->map->map[map_x][map_y] == WALL)
// 				hit = true;
// 		}
// 		if (game->ray.side == 0)
// 			game->ray.length = (game->ray.side_dist.x - game->ray.delta_dist.x);
// 		else
// 			game->ray.length = (game->ray.side_dist.y - game->ray.delta_dist.y);
// 		compute_pixel_column(game, x);
// 		x++;
// 	}
// }
