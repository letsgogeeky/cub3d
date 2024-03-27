#include "../../../include/cube.h"

void	load_textures(t_map *map)
{
	map->north_texture->tex = mlx_load_png(map->north_texture->path);
	map->south_texture->tex = mlx_load_png(map->south_texture->path);
	map->east_texture->tex =  mlx_load_png(map->east_texture->path);
	map->west_texture->tex =  mlx_load_png(map->west_texture->path);
	if (map->door_texture->path)
		map->door_texture->tex =  mlx_load_png(map->door_texture->path);
	printf("load_textures\n");
}

mlx_texture_t	*choose_texture(t_game *game)
{
	if (game->ray.wall_texture == NORTH)
		return (game->map->north_texture->tex);
	else if (game->ray.wall_texture == SOUTH)
		return (game->map->south_texture->tex);
	else if (game->ray.wall_texture == EAST)
		return (game->map->east_texture->tex);
	else if (game->ray.wall_texture == WEST)
		return (game->map->west_texture->tex);
	else
		return (NULL);
}

int	find_color(mlx_texture_t *txt, double x, double y)
{
	// int	a;
	// int	b;
	int		i;
	double	n;
	int		color;

	// a = (int)x;
	// b = (int)y;
	i = (int)y % txt->width;
	n = x * txt->height + i;
	color = txt->pixels[(int)n];
	return (color);
}

int	interpolate(mlx_texture_t *txt, double col, double y)
{
	double	x1;
	double	x2;
	double	y1;
	double	y2;
	int		color1;
	int		color2;
	int		color;

	x1 = (int)col;
	x2 = x1 + 1.0;
	y1 = (int)y;
	y2 = y1 + 1.0;
	color1 = (col - (double)x1) * find_color(txt, x1, y1) + ((double)x2 - col) * find_color(txt, x2, y1);
	color2 = (col - (double)x1) * find_color(txt, x1, y2) + ((double)x2 - col) * find_color(txt, x2, y2);
	color = color1 * (y - y1) + color2 * (y2 - y);
	return (color);
}

void	resze_tex(mlx_texture_t *normal, t_game *game, t_column *column, int x)
{
	// double	factor;
	double	pos_on_wall;
	double	col;
	int		n;
	double	j;
	int		color;

	// factor = game->ray.wall_height / normal->height;
	if (game->ray.wall_texture == NORTH || game->ray.wall_texture == SOUTH)
		pos_on_wall = game->ray.hitpoint.x - (int)game->ray.hitpoint.x;
	else if (game->ray.wall_texture == WEST || game->ray.wall_texture == EAST)
		pos_on_wall = game->ray.hitpoint.y - (int)game->ray.hitpoint.y;
	else
		pos_on_wall = 0;
	col = normal->width * pos_on_wall;
	n = column->end_ceiling;
	j = 0;
	while (n < column->start_floor)
	{
		// color = 0x0000CD;
		color = interpolate(normal, col, j);
		mlx_put_pixel(game->image, x, n, color);
		j = j + normal->height / (column->start_floor - n);
		n++;
	}
}
