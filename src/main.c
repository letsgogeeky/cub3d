#include "cube.h"

void	show_help(void)
{
	printf("\033[36m");
	printf("Hey, it's Cub3D! here are the list of controls:\n");
	printf("W A S D :: Controls the player movement\n");
	printf("F       :: Open/Close the door\n");
	printf("SPACE   :: Enable/Disable Mouse\n");
	printf("M       :: Enable/Disable Minimap\n");
	printf("LEFT / RIGHT arrows :: Rotate the player\n");
	printf("Mouse               :: Rotate the player\n");
	printf("---------------------------------------\n");
	printf("ESC		:: Exit the game\n");
	printf("---------------------------------------\n");
}

int	main(int ac, char **argv)
{
	t_map	*m;
	int		fd;

	if (ac == 2)
	{
		if (check_end(argv[1]))
			return (1);
		m = ft_calloc(1, sizeof(t_map));
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (ft_prerr(INV_FD, NULL), 1);
		if (parse(m, fd, argv[1]) == NULL)
			return (ft_prerr(PARSING_FAILED, NULL), 1);
		printf("parsing done\n");
		if (validate(m) == 0)
			return (ft_prerr(INV_MAP, NULL), 1);
		printf("validation done. map is valid!\n");
		show_help();
		open_n_draw(m);
	}
	else
		return (ft_prerr(WRONG_ARG, NULL), 1);
	return (0);
}
