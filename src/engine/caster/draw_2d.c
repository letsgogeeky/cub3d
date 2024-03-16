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

	block_size = game->block_size;
	
	start.x = game->player.pos.x * block_size + block_size / 2;
	start.y = game->player.pos.y * block_size + block_size / 2;
	// game->ray.angle.x = game->player.dir.x + game->player.plane.x;
	// game->ray.angle.y = game->player.dir.y + game->player.plane.y;
	// end.x = game->ray.angle.x * block_size + start.x;
	// end.y = game->ray.angle.y * block_size + start.y;
	// end.x = (game->ray.angle.x * block_size) + start.x;
	// end.y = (game->ray.angle.y * block_size) + start.y;
	// draw_line(game, start, end, color);



	// if (game->ray.step_for_plus_x.x < 0)
	// 	end.x = ((game->ray.step_for_plus_x.x + 0.5) * block_size) + start.x;
	// else 
	// 	end.x = ((game->ray.step_for_plus_x.x - 0.5) * block_size) + start.x;
	// if (game->ray.step_for_plus_x.y < 0)
	// 	end.y = ((game->ray.step_for_plus_x.y + 0.5) * block_size) + start.y;
	// else
	// 	end.y = ((game->ray.step_for_plus_x.y - 0.5) * block_size) + start.y;
	end.x = game->ray.hitpoint.x;
	end.y = game->ray.hitpoint.y;


	draw_line(game, start, end, color);
	// if (game->ray.step_for_plus_y.x < 0)
	// 	end.x = ((game->ray.step_for_plus_y.x + 0.5) * block_size) + start.x;
	// else
	// 	end.x = ((game->ray.step_for_plus_y.x - 0.5) * block_size) + start.x;

	// if (game->ray.step_for_plus_y.y < 0)
	// 	end.x = ((game->ray.step_for_plus_y.y + 0.5) * block_size) + start.x;
	// else
	// 	end.x = ((game->ray.step_for_plus_y.y - 0.5) * block_size) + start.x;
	// draw_line(game, start, end, color);
}
