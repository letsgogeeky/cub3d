#include "cube.h"

t_ray	init_ray(void)
{
	t_ray	ray;

	ray.angle.x = 0;
	ray.angle.y = 0;
	ray.dir.x = 0;
	ray.dir.y = 0;
	ray.side_dist.x = 0;
	ray.side_dist.y = 0;
	ray.delta_dist.x = 0;
	ray.delta_dist.y = 0;
	return (ray);
}

void	draw_line(t_game *game, t_vector start, t_vector end, int color)
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	steps;
	double	i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	dx /= steps;
	dy /= steps;
	x = start.x;
	y = start.y;
	i = 0;
	while (i <= steps)
	{
		mlx_put_pixel(game->graphics->image, x, y, color);
		x += dx;
		y += dy;
		i++;
	}
}

t_vector	distance_to_wall(t_game *game)
{
	t_vector	distance;
	int x;
	int y;

	distance.x = 0;
	distance.y = 0;
	x = (int)(game->player.pos.y + distance.y);
	y = (int)(game->player.pos.x + distance.x);
	while (game->map->map[x][y] && game->map->map[x][y] != WALL)
	{
		distance.x++;
		distance.y++;
		x = (int)(game->player.pos.y + distance.y);
		y = (int)(game->player.pos.x + distance.x);
	}
	return (distance);

}


void	visualize_2d_ray(t_game *game, int color)
{
	t_vector	start;
	t_vector	end;
	t_vector	distance;
	int		block_size;

	block_size = game->block_size;
	distance = distance_to_wall(game);
	start.x = game->player.pos.x * block_size + block_size / 2;
	start.y = game->player.pos.y * block_size + block_size / 2;
	end.x = game->player.dir.x * block_size + start.x + (distance.x * block_size);
	end.y = game->player.dir.y * block_size + start.y + (distance.y * block_size);
	ft_printf("start: %f, %f\n", start.x, start.y);
	ft_printf("end: %f, %f\n", end.x, end.y);
	draw_line(game, start, end, color);
}
