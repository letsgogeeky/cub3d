#include "../../../include/cube.h"

void	draw_ceiling(t_game *game, t_column *column, int x)
{
	int	i;
	int	color;

	i = 0;
	color = game->map->ceiling_color->hex_color_rgb;
	while (i < column->end_ceiling)
	{
		mlx_put_pixel(game->image, x, i, color);
		i++;
	}
}

void	draw_floor(t_game *game, t_column *column, int x)
{
	int	i;
	int	color;

	i = column->start_floor;
	color = game->map->floor_color->hex_color_rgb;
	while (i < HEIGHT)
	{
		mlx_put_pixel(game->image, x, i, color);
		i++;
	}
}

void	draw_image(t_game *game, t_column *column, int x)
{
	t_texture	*normal;

	normal = choose_texture(game);
	resze_tex(normal, game, column, x);
}

void	draw_column(t_game *game, t_column *column, int x)
{
	draw_image(game, column, x);
	draw_ceiling(game, column, x);
	draw_floor(game, column, x);
}
