#include "../../../include/cube.h"

void	resze_tex(t_texture *normal, t_game *game, t_column *column, int x)
{
	double	col;
	int		n;
	double	j;
	double	step;
	double	y;
	double	y1;

	if (game->ray.wall_texture == NORTH || game->ray.wall_texture == SOUTH)
		col = normal->width * fmod(game->ray.hitpoint.x, 1);
	else
		col = normal->width * fmod(game->ray.hitpoint.y, 1);
	y1 = (HEIGHT - column->wall_height) / 2;
	if (y1 >= 0 || column->wall_height >= HEIGHT)
		y = 0;
	else
		y = normal->height / column->wall_height * fabs(y1);
	step = 1.0 * normal->height / column->wall_height;
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
