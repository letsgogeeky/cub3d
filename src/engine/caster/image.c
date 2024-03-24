#include "../../../include/cube.h"

void	load_textures(t_map *map)
{
	map->north_texture->tex = mlx_load_png("assets/textures/flowers.png");
	map->south_texture->tex = mlx_load_png("assets/textures/plants.png");
	map->east_texture->tex =  mlx_load_png("assets/textures/wall.png");
	map->west_texture->tex =  mlx_load_png("assets/textures/bricks.png");
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
