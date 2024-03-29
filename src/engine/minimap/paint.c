#include "cube.h"

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

void	clear_image(mlx_image_t *image, int width, int height)
{
    int	x;
    int	y;

    x = 0;
    y = 0;
    while (y < height)
    {
        while (x < width)
        {
            mlx_put_pixel(image, x, y, 0x00000000);
            x++;
        }
        x = 0;
        y++;
    }
}