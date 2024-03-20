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
		mlx_put_pixel(game->image, x, y, color);
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
//	int			round_x;
//	int			round_y;

	block_size = game->block_size;
	
	start.x = game->player.pos.x * block_size /*+ block_size / 2.0*/;
	start.y = game->player.pos.y * block_size /*+ block_size / 2.0*/;
	//round_x = (int)game->ray.hitpoint.x;
	//round_y = (int)game->ray.hitpoint.y;
	//end.x = (float)round_x * block_size;
	//end.y = (float)round_y * block_size;
	end.x = game->ray.hitpoint.x * block_size;
	end.y = game->ray.hitpoint.y * block_size;

	printf("START: %f/%f END: %f/%f\n", start.x, start.y, end.x, end.y);
	draw_line(game, start, end, color);
}
