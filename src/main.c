#include "cube.h"

// int	main()
// {
// 	test_with_mocks();
// 	t_game	*game;

// 	game = init_game();
// 	if (!game)
// 	{
// 		printf("Error: failed to initialize game\n");
// 		return (1);
// 	}
// 	mlx_image_to_window(game->graphics->mlx, game->graphics->image, 0, 0);
// 	mlx_loop(game->graphics->mlx);
// 	return (0);
// }

int	main(int ac, char **argv)
{
	t_map	*m;
	int		fd;

	if (ac == 2)
	{
		m = ft_calloc(1, sizeof(t_map));
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (ft_prerr(INV_FD, NULL), 1);
		if (parse(m, fd, argv[1]) == NULL)
			return (ft_prerr(PARSING_FAILED, NULL), 1);
	}
	else
		return (ft_prerr(WRONG_ARG, NULL), 1);
	free_map_struct(m);
	return (0);
}
