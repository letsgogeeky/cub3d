#include "../../../include/cube.h"

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.angle.x = 0;
	ray.angle.y = 0;
	ray.dir.x = 0;
	ray.dir.y = 0;
	ray.side_dist_x.x = 0;
	ray.side_dist_x.y = 0;
	ray.side_dist_y.x = 0;
	ray.side_dist_y.y = 0;
	ray.delta_dist.x = 0;
	ray.delta_dist.y = 0;
	ray.map.x = 0;
	ray.map.y = 0;
	ray.step.x = 0;
	ray.step.y = 0;
	return (ray);
}

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

void	visualize_2d_ray(t_game *game, int color)
{
	int			block_size;
	int			x;


	block_size = game->block_size;
	x = 0;
	while (x < AMOUNT_RAYS_2D_FOV)
	{
		printf("*************Count %x\n", x);
		set_angle(game, x);
		set_steps(game);
		calculate_hitpoint(game);
		draw_ray(game, color);
		printf("\n");
		x++;
		// test_parsing(game->map, game->map->rows);

	}
	return;

	// game->ray.map.x = game->player.pos.x;
	// game->ray.map.y = game->player.pos.y;
	// while (!hit)
	// {
	// 	if (check_hit(game) != 0)
	// 	{
	// 		set_direction_wall(game);
	// 		break;
	// 	}
		
	// }

}

	// 	if (game->ray.side_dist.x < game->ray.side_dist.y)
	// 	{
	// 		game->ray.side_dist.x += game->ray.delta_dist.x;
	// 		game->ray.map.x += game->ray.step.x;
	// 		game->ray.side = 0;
	// 	}
	// 	else
	// 	{
	// 		game->ray.side_dist.y += game->ray.delta_dist.y;
	// 		game->ray.map.y += game->ray.step.y;
	// 		game->ray.side = 1;
	// 	}
	// 	int map_x = (int)game->ray.map.x;
	// 	int map_y = (int)game->ray.map.y;
	// 	if (map_x < 0 || map_y < 0 || map_x >= game->map->rows || map_y >= game->map->cols)
	// 		break;
	// 	if (game->map->map[map_x][map_y] && game->map->map[map_x][map_y] == WALL)
	// 		hit = true;
	// if (game->ray.side == 0)
	// 	game->ray.length = (game->ray.side_dist.x - game->ray.delta_dist.x);
	// else
	// 	game->ray.length = (game->ray.side_dist.y - game->ray.delta_dist.y);

	// // ft_printf("map.x: %f, map.y: %f\n", game->ray.map.x, game->ray.map.y);
	// end.x = (int)game->ray.map.x * block_size + start.x;
	// end.y = (int)game->ray.map.y * block_size + start.y;
	// // ft_printf("end.x: %f, end.y: %f\n", end.x, end.y);
	// draw_line(game, start, end, color);
	// // x++;

	// // ft_printf("start: %f, %f\n", start.x, start.y);
	// // ft_printf("end: %f, %f\n", end.x, end.y);

void	compute_pixel_column(t_game *game, int x)
{
	double	wall_hit;
	t_vector	wall;
	int		wall_height;
	int	y;

	wall_height = (int)(HEIGHT / game->ray.length);
	wall.x = (-wall_height / 2 + HEIGHT / 2);
	if (wall.x < 0)
		wall.x = 0;
	wall.y = (wall_height / 2 + HEIGHT / 2);
	if (wall.y >= HEIGHT)
		wall.y = HEIGHT - 1;
	if (game->ray.side == 0)
		wall_hit = game->player.pos.y + game->ray.length * game->ray.angle.y;
	else
		wall_hit = game->player.pos.x + game->ray.length * game->ray.angle.x;
	wall_hit -= floor(wall_hit);

	y = 0;
	while (y < HEIGHT)
	{
		if (y < wall.x)
			mlx_put_pixel(game->image, x, y, 0x00FF0000);
		else if (y > wall.x && y < wall.y)
			mlx_put_pixel(game->image, x, y, 0x00FFFFFF);
		else
			mlx_put_pixel(game->image, x, y, 0x000000FF);
		y++;
	
	}
}


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
