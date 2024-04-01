#include "cube.h"

void	draw_vert(t_game *game, int block_size)
{
	int	y;
	int	x;
	int	cnt;

	if (!game->enable_minimap)
		return ;
	y = 0;
	x = 0;
	cnt = 0;
	while (cnt <= game->map->cols)
	{
		while (y < block_size * game->map->rows)
		{
			mlx_put_pixel(game->minimap->image, x, y, MINIMAP_FLOOR);
			y++;
		}
		y = 0;
		x = x + block_size;
		cnt++;
	}
}

void	draw_hor(t_game *game, int block_size)
{
	int	y;
	int	x;
	int	cnt;

	if (!game->enable_minimap)
		return ;
	y = 0;
	x = 0;
	cnt = 0;
	while (cnt <= game->map->rows)
	{
		while (x < block_size * (game->map->cols))
		{
			mlx_put_pixel(game->minimap->image, x, y, MINIMAP_FLOOR);
			x++;
		}
		x = 0;
		y = y + block_size;
		cnt++;
	}
}

void	draw_circle(mlx_image_t *image, t_position point, int radius, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < radius * 2)
	{
		while (j < radius * 2)
		{
			if (sqrt_xy_squared((i - radius), (j - radius)) <= radius)
				mlx_put_pixel(image, point.x + i, point.y + j, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	show_player(t_game *game)
{
	game->player.coordinate.x = game->player.pos.x * \
	game->block_size - game->minimap->p_radius;
	game->player.coordinate.y = game->player.pos.y * \
	game->block_size - game->minimap->p_radius;
	if (!game->enable_minimap)
	{
		visualize_3d(game);
		return ;
	}
	draw_circle(game->minimap->image, \
		game->player.coordinate, game->minimap->p_radius, \
		MINIMAP_PLAYER);
	visualize_2d_ray(game, MINIMAP_DIR);
	visualize_3d(game);
}

void	draw_block(t_game *game)
{
	int	block_size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	block_size = game->block_size;
	clear_image(game->minimap->image, game->minimap->width, \
	game->minimap->height);
	while (i < game->map->rows)
	{
		while (game->map->map[i][j] != '\0')
		{
			if (game->map->map[i][j] == WALL)
				fill_block(game, j * block_size, i * block_size, MINIMAP_WALL);
			else if (game->map->map[i][j] == DOOR)
				fill_door(game, j, i, MINIMAP_DOOR);
			j++;
		}
		j = 0;
		i++;
	}
	draw_vert(game, block_size);
	draw_hor(game, block_size);
	show_player(game);
}
