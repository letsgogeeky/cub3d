#include "cube.h"

int	main()
{
	void	*mock_functions[] = {
		&mock_map_shifted_section_invalid,
		&mock_map_shifted_section_valid,
		&mock_map_with_spaces_invalid,
		&mock_base_map_valid,
		NULL
	};

	int	i;

	i = 0;
	while (mock_functions[i])
	{
		t_map	*map;
		map = ((t_map *(*)(void))mock_functions[i])();
		int	result;
		result = validate(map);

		if (result)
			ft_printf("Map is valid\n");
		else
			ft_printf("Map is invalid\n");
			i++;
	}
	return (0);
}
