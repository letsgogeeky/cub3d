#include "../../../include/cube.h"

void	load_textures(t_game *game)
{
	game->map->north_texture = mlx_load_png("../../assets/textures/flower.png");
	game->map->south_texture = mlx_load_png("../../assets/textures/concrete.png");
	game->map->east_texture = mlx_load_png("../../assets/textures/plant.png");
	game->map->west_texture = mlx_load_png("../../assets/textures/brick.png");
}

int	main(int ac, char **argv)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	image = mlx_new_image(mlx, WIDTH, HEIGHT);
		if (!image)
	{
		mlx_terminate(game->mlx);
		return (NULL);
	}
	return (0);
}

