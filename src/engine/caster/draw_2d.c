#include "../../../include/cube.h"

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
	while (i <= steps && x > 0 && y > 0 && x < WIDTH && y < HEIGHT)
	{
		mlx_put_pixel(game->minimap->image, x, y, color);
		x += dx;
		y += dy;
		i++;
	}
}

void	draw_ray(t_game *game, int color)
{
	int			block_size;
	t_vector	start;
	t_vector	end;

	block_size = game->block_size;
	start.x = game->player.pos.x * block_size;
	start.y = game->player.pos.y * block_size;
	end.x = game->ray.hitpoint.x * block_size;
	end.y = game->ray.hitpoint.y * block_size;
	draw_line(game, start, end, color);
}
