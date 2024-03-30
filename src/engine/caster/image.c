#include "cube.h"

double	set_col(t_game *game, t_texture *normal)
{
	int	col;

	if (game->ray.wall_texture == NORTH || game->ray.wall_texture == SOUTH)
		col = normal->width * fmod(game->ray.hitpoint.x, 1);
	else
		col = normal->width * fmod(game->ray.hitpoint.y, 1);
	return (col);
}

void	set_short(t_texture *normal, t_game *game, double *y, double *step)
{
	(*y) = (double)normal->height / 2.0 - 0.5 * (double)normal->height * \
		((double)HEIGHT / game->ray.wall_height);
	(*step) = (double)normal->height / (game->ray.wall_height \
		/ (double)HEIGHT) / (double)HEIGHT;
}

void	resze_tex(t_texture *normal, t_game *game, t_column *column, int x)
{
	double	col;
	double	j;
	double	step;
	double	y;
	int		n;

	col = set_col(game, normal);
	y = 0;
	step = 1.0 * normal->height / column->wall_height;
	if (game->ray.wall_height >= (double)HEIGHT)
		set_short(normal, game, &y, &step);
	j = ((int)y * normal->width) + col;
	n = column->end_ceiling;
	while (n < column->start_floor && n < HEIGHT)
	{
		if (j > normal->width * normal->height)
			j = normal->width * normal->height - 1;
		mlx_put_pixel(game->image, x, n, normal->pixels[(int)j]);
		y += step;
		j = ((int)y * normal->width) + col;
		n++;
	}
}
