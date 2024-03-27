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
	// int				i;
	// int				color;
	t_texture	*normal;
	// mlx_texture_t	*resized;

	// i = column->end_ceiling;
	// printf("start floor: %i, start ceiling: %i\n", column->start_floor ,column->end_ceiling);
	normal = choose_texture(game);
	resze_tex(normal, game, column, x);
	// while (i < column->start_floor)
	// {
	// 	color = 0xFFFFFFFF;
	// 	mlx_put_pixel(game->image, x, i, color);
	// 	i++;
	// }
}

void	draw_complete(t_game *game, int x)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		mlx_put_pixel(game->image, x, i, 0xFFFFFFFF);
		i++;
	}
}

void	draw_column(t_game *game, t_column *column, int x)
{
	// if (column->wall_height + 2 >= HEIGHT)
	// {
	// 	draw_complete(game, x);
	// 	return ;
	// }
	draw_image(game, column, x);
	draw_ceiling(game, column, x);
	draw_floor(game, column, x);
}
