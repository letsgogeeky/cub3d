#include "cube.h"

int	main()
{
	t_map	*map;
	int	result;

	map = mock_base_map_valid();
	result = validate(map);

	if (result)
		ft_printf("Map is valid\n");
	else
		ft_printf("Map is invalid\n");
}
