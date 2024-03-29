# include "cube.h"

void	fill_block(t_game *game, int x, int y, int color)
{
	int	tmp_x;
	int	x_max;
	int	y_max;

	tmp_x = x;
	x_max = x + game->block_size;
	y_max = y + game->block_size;
	while (y < y_max)
	{
		while (x < x_max)
		{
			mlx_put_pixel(game->minimap->image, x, y, color);
			x++;
		}
		x = tmp_x;
		y++;
	}
}

void	fill_door(t_game *game, int x, int y, int color)
{
	int	tmp_x;
	int	x_max;
	int	y_max;
	int	margin;
	bool	is_open;

	is_open = door_is_open(game, y, x);
	margin = 0;
	if (is_open)
		margin = game->block_size - (game->block_size / 10);
	x = x * game->block_size;
	y = y * game->block_size;
	x_max = x + game->block_size;
	y_max = y + game->block_size;
	x = x + margin;
	tmp_x = x;
	while (y < y_max)
	{
		while (x < x_max)
		{
			mlx_put_pixel(game->minimap->image, x, y, color);
			x++;
		}
		x = tmp_x;
		y++;
	}
}

void	draw_vert(t_game *game, int block_size)
{
	int	y;
	int	x;
	int	cnt;

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

	y = 0;
	x = 0;
	cnt = 0;
	while (cnt <= game->map->rows)
	{
		while (x < block_size * (game->map->cols)) // why one more column then chars
		{
			mlx_put_pixel(game->minimap->image, x, y, MINIMAP_FLOOR);
			x++;
		}
		x = 0;
		y = y + block_size;
		cnt++;
	}
}

void	cast_wall(t_game *game, int size, int x, int y, int color)
{
	int	tmp_x;
	int	x_max;
	int	y_max;

	tmp_x = x;
	x_max = x + size;
	y_max = y + size;
	while (y < y_max)
	{
		while (x < x_max)
		{
			mlx_put_pixel(game->image, x, y, color);
			x++;
		}
		x = tmp_x;
		y++;
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
	game->player.coordinate.x = game->player.pos.x * game->block_size - game->minimap->p_radius;
	game->player.coordinate.y = game->player.pos.y * game->block_size - game->minimap->p_radius;
	draw_circle(game->minimap->image, \
		game->player.coordinate, game->minimap->p_radius, \
		MINIMAP_PLAYER);
	visualize_2d_ray(game, MINIMAP_DIR);
}

void	draw_block(t_game *game)
{
	int	block_size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	block_size = game->block_size;
	clear_image(game->minimap->image, game->minimap->width, game->minimap->height);
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
