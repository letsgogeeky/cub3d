#include "../../../include/cube.h"

unsigned int	*load_texture_pixels(mlx_texture_t *texture)
{
	unsigned int	*data;
	u_int32_t		i;
	u_int32_t		j;

	data = malloc(sizeof(unsigned int) * texture->width * texture->height);
	if (!data)
		return (NULL);
	i = 0;
	while (i < texture->height)
	{
		j = 0;
		while (j < texture->width)
		{
			data[i * texture->width + j] = colorcode(
				texture->pixels[i * texture->width * 4 + j * 4],
				texture->pixels[i * texture->width * 4 + j * 4 + 1],
				texture->pixels[i * texture->width * 4 + j * 4 + 2],
				texture->pixels[i * texture->width * 4 + j * 4 + 3]
			);
			j++;
		}
		i++;
	}
	// mlx_delete_texture(texture);
	return (data);
}

void	load_textures(t_map *map) //doesnt seem to work probably used wrongly
{
	map->north_texture->tex = mlx_load_png(map->north_texture->path);
	map->north_texture->pixels = load_texture_pixels(map->north_texture->tex);
	map->south_texture->tex = mlx_load_png(map->south_texture->path);
	map->south_texture->pixels = load_texture_pixels(map->south_texture->tex);
	map->east_texture->tex =  mlx_load_png(map->east_texture->path);
	map->east_texture->pixels = load_texture_pixels(map->east_texture->tex);
	map->west_texture->tex =  mlx_load_png(map->west_texture->path);
	map->west_texture->pixels = load_texture_pixels(map->west_texture->tex);
	if (map->door_texture->path)
		map->door_texture->tex =  mlx_load_png(map->door_texture->path);
	printf("load_textures\n");
}

t_texture	*choose_texture(t_game *game)
{
	if (game->ray.wall_texture == NORTH)
		return (game->map->north_texture);
	else if (game->ray.wall_texture == SOUTH)
		return (game->map->south_texture);
	else if (game->ray.wall_texture == EAST)
		return (game->map->east_texture);
	else if (game->ray.wall_texture == WEST)
		return (game->map->west_texture);
	else
		return (NULL);
}

int	find_color(t_texture *txt, double x, double y)
{
	// int	a;
	// int	b;
	// int	i;
	// double	n;
 	int	color;

	// a = (int)x;
	// b = (int)y;
	// i = (int)y % txt->width * 4;
	// n = (x * txt->height) + i;
	if ((txt->tex->height * x + (int)y + 1) > txt->tex->height * txt->tex->width)
	{
		//TODO: remove this after debugging (preventing segfaults to observe behavior)
		printf("navigating to (int)(txt->tex->height * x + (int)y + 1): %i\n", (int)(txt->tex->height * x + (int)y + 1));
		printf("texture array size: %i\n", txt->tex->height * txt->tex->width);
		return (MINIMAP_DIR);
	}
	color = txt->pixels[(int)(txt->tex->height * x + (int)y)];
	return (color);
}

// int	interpolate(t_texture *txt, double col, double y)
// {
// 	double	x1;
// 	double	x2;
// 	double	y1;
// 	double	y2;
// 	int		color1;
// 	int		color2;
// 	int		color;

// 	x1 = (int)col;
// 	x2 = x1 + 1.0;
// 	y1 = (int)y;
// 	y2 = y1 + 1.0;
// 	color1 = (col - (double)x1) * find_color(txt, x1, y1) + ((double)x2 - col) * find_color(txt, x2, y1);
// 	color2 = (col - (double)x1) * find_color(txt, x1, y2) + ((double)x2 - col) * find_color(txt, x2, y2);
// 	color = color1 * (y - y1) + color2 * (y2 - y);
// 	return (color);
// }

void	resze_tex(t_texture *normal, t_game *game, t_column *column, int x)
{
	double	col;
	int		n;
	double	j;
	double	step;
	double	y;
	double	y1;

	if (game->ray.wall_texture == NORTH || game->ray.wall_texture == SOUTH)
		col = normal->tex->width * fmod(game->ray.hitpoint.x, 1);
	else
		col = normal->tex->width * fmod(game->ray.hitpoint.y, 1);
	y1 = (HEIGHT - column->wall_height) / 2;
	if (y1 >= 0 || column->wall_height >= HEIGHT)
		y = 0;
	else
		y = normal->tex->height / column->wall_height * fabs(y1);
	step = 1.0 * normal->tex->height / column->wall_height;
	n = column->end_ceiling;
	j = ((int)y * normal->tex->width) + col;
	while (n < column->start_floor && n < HEIGHT)
	{
		if (j > normal->tex->width * normal->tex->height)
			j = normal->tex->width * normal->tex->height - 1;
		mlx_put_pixel(game->image, x, n, normal->pixels[(int)j]);
		y+= step;
		j = ((int)y * normal->tex->width) + col;
		n++;
	}
}
