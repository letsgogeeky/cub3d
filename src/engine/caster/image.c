#include "../../../include/cube.h"

void	load_textures(t_map *map)
{
	map->north_texture->tex = mlx_load_png("assets/textures/flowers.png");
	map->south_texture->tex = mlx_load_png("assets/textures/plants.png");
	map->east_texture->tex =  mlx_load_png("assets/textures/wall.png");
	map->west_texture->tex =  mlx_load_png("assets/textures/bricks.png");
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

// int	interpolate(mlx_texture_t *txt, double col, double y, double factor)
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
// 	color1 = (col - x1) * farbex1y1 + (x2 - col) *farbex2y1;
// 	color2 = (col - x1) * farbex1y2 + (x2 - col) *farbex2y2;
// 	color = color1 * (y - y1) + color2 * (y2 - y);
// 	return (color);
// }

void	resze_tex(mlx_texture_t *normal, t_game *game, t_column *column, int x)
{
	double	factor;
	double	pos_on_wall;
	double	col;
	int		n;
	double	j;
	int		color;

	factor = game->ray.wall_height / normal->height;
	if (game->ray.wall_texture == NORTH || game->ray.wall_texture == SOUTH)
		pos_on_wall = game->ray.hitpoint.x - (int)game->ray.hitpoint.x;
	if (game->ray.wall_texture == WEST || game->ray.wall_texture == EAST)
		pos_on_wall = game->ray.hitpoint.y - (int)game->ray.hitpoint.y;
	col = normal->width * pos_on_wall;
	n = column->end_ceiling;
	j = 0;
	while (n < column->start_floor)
	{
		color = 0x0000CD;
		// color = interpolate(normal, col, j, factor);
		mlx_put_pixel(game->image, x, n, color);
		j = j + normal->height / (column->start_floor - n);
		n++;
	}
}

// int	main()
// {
// 	mlx_t			*mlx;
// 	mlx_image_t		*image;
// 	mlx_texture_t	*texture;

// 	mlx = mlx_init(WIDTH, HEIGHT, "textures", false);
// 	// image = mlx_new_image(mlx, WIDTH, HEIGHT);
// 	texture = mlx_load_png("assets/textures/flowers.png");
// 	if (!texture)
// 	{
// 		mlx_terminate(mlx);
// 		return (0);
// 	}
// 	image = mlx_texture_to_image(mlx, texture);
// 	if (mlx_image_to_window(mlx, image, 0, 0) < 0)
// 	{
// 		mlx_terminate(mlx);
// 		return (0);
// 	}
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (0);
// }
