#include "../../../include/cube.h"

void	draw_line(t_game *game, t_vector start, t_vector end, int color)
{
	double	dx;
	double	dy;
	double	steps;
	double	i;

	dx = end.x - start.x;
	dy = end.y - start.y;
	steps = fabs(dy);
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	dx /= steps;
	dy /= steps;
	i = 0;
	while (i <= steps && start.x > 0 && start.y > 0 \
		&& start.x < WIDTH && start.y < HEIGHT)
	{
		mlx_put_pixel(game->minimap->image, start.x, start.y, color);
		start.x += dx;
		start.y += dy;
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
