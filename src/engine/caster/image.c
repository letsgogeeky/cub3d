#include "cube.h"

void	resze_tex(t_texture *normal, t_game *game, t_column *column, int x)
{
	double	col;
	int		n;
	double	j;
	double	step;
	double	y;

	if (game->ray.wall_texture == NORTH || game->ray.wall_texture == SOUTH)
		col = normal->width * fmod(game->ray.hitpoint.x, 1);
	else
		col = normal->width * fmod(game->ray.hitpoint.y, 1);
	y = 0;
	if (game->ray.wall_height >= (double)HEIGHT)
		y = (double)normal->height / 2.0 - 0.5 * (double)normal->height * ((double)HEIGHT / game->ray.wall_height);
	step = 1.0 * normal->height / column->wall_height;
	if (game->ray.wall_height >= (double)HEIGHT)
		step = (double)normal->height / (game->ray.wall_height / (double)HEIGHT) / (double)HEIGHT;
	n = column->end_ceiling;
	j = ((int)y * normal->width) + col;
	while (n < column->start_floor && n < HEIGHT)
	{
		if (j > normal->width * normal->height)
			j = normal->width * normal->height - 1;
		mlx_put_pixel(game->image, x, n, normal->pixels[(int)j]);
		y+= step;
		j = ((int)y * normal->width) + col;
		n++;
	}
}
