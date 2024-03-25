#include "cube.h"


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
		open_n_draw(m);
	}
	else
		return (ft_prerr(WRONG_ARG, NULL), 1);
	return (0);
}
