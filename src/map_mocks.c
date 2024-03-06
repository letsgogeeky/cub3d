#include "cube.h"

t_map	*mock_map_shifted_section_invalid()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * 15);
	map->map[0] =  ft_strdup("        1111111111111111111111111");
	map->map[1] =  ft_strdup("        1000000000110000000000001");
	map->map[2] =  ft_strdup("        1011000001110000000000001");
	map->map[3] =  ft_strdup("        1001000000000000000000001");
	map->map[4] =  ft_strdup("111100011011000001110000000000001");
	map->map[5] =  ft_strdup("100000000011000001110111111111111");
	map->map[6] =  ft_strdup("11110111111111011100000010001    ");
	map->map[7] =  ft_strdup("11110111111111011101010010001    ");
	map->map[8] =  ft_strdup("11000000110101011100000010001    ");
	map->map[9] =  ft_strdup("10000000000000001100000010001    ");
	map->map[10] = ft_strdup("10000000000000001101010010001    ");
	map->map[11] = ft_strdup("11000001110101011111011110N0111  ");
	map->map[12] = ft_strdup("11110111 1110101 101111010001    ");
	map->map[13] = ft_strdup("11111111 1111111 111111111111    ");
	map->map[14] = NULL;
	return (map);
}

t_map	*mock_map_shifted_section_valid()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * 15);
	map->map[0] =  ft_strdup("        1111111111111111111111111");
	map->map[1] =  ft_strdup("        1000000000110000000000001");
	map->map[2] =  ft_strdup("        1011000001110000000000001");
	map->map[3] =  ft_strdup("        1001000000000000000000001");
	map->map[4] =  ft_strdup("111111111011000001110000000000001");
	map->map[5] =  ft_strdup("100000000011000001110111111111111");
	map->map[6] =  ft_strdup("11110111111111011100000010001    ");
	map->map[7] =  ft_strdup("11110111111111011101010010001    ");
	map->map[8] =  ft_strdup("11000000110101011100000010001    ");
	map->map[9] =  ft_strdup("10000000000000001100000010001    ");
	map->map[10] = ft_strdup("10000000000000001101010010001    ");
	map->map[11] = ft_strdup("11000001110101011111011110N0111  ");
	map->map[12] = ft_strdup("11110111 1110101 101111010001    ");
	map->map[13] = ft_strdup("11111111 1111111 111111111111    ");
	map->map[14] = NULL;
	return (map);
}

t_map	*mock_map_with_spaces_invalid()
{
	t_map	*map;

	// for this shape, the walls check should be extended to the surrounding lines
	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * 11);
	map->map[0] = ft_strdup(" 1111111111    ");
	map->map[1] = ft_strdup("100000000000001");
	map->map[2] = ft_strdup("100000000000001");
	map->map[3] = ft_strdup("100000000000001");
	map->map[4] = ft_strdup("100000000000001");
	map->map[5] = ft_strdup("100000000100011");
	map->map[6] = ft_strdup("100000000000001");
	map->map[7] = ft_strdup("100000000000001");
	map->map[8] = ft_strdup("100000000000001");
	map->map[9] = ft_strdup("   111111111111");
	map->map[10] = NULL;
	return (map);
}

t_map	*mock_base_map_valid()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * 11);
	map->map[0] = ft_strdup("111111111111111");
	map->map[1] = ft_strdup("100000000000001");
	map->map[2] = ft_strdup("100000000000001");
	map->map[3] = ft_strdup("100000000000001");
	map->map[4] = ft_strdup("100000000000001");
	map->map[5] = ft_strdup("100000000100011");
	map->map[6] = ft_strdup("100000000000001");
	map->map[7] = ft_strdup("100000000000001");
	map->map[8] = ft_strdup("1000000000W0001");
	map->map[9] = ft_strdup("111111111111111");
	map->map[10] = NULL;
	return (map);
}

t_map	*mock_passage_map_valid()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * 13);
	map->map[0] =  ft_strdup("111111111111111");
	map->map[1] =  ft_strdup("100000000000001");
	map->map[2] =  ft_strdup("100000000000001");
	map->map[3] =  ft_strdup("100000000000001");
	map->map[4] =  ft_strdup("100000000000001");
	map->map[5] =  ft_strdup("100000000100011");
	map->map[6] =  ft_strdup("100000000000001");
	map->map[7] =  ft_strdup("100000000000001");
	map->map[8] =  ft_strdup("1000000000W0001");
	map->map[9] =  ft_strdup("111111111111111");
	map->map[10] = ft_strdup("111111000011111");
	map->map[11] = ft_strdup("11111 1111 1111");
	map->map[12] = NULL;
	return (map);
}

t_map	*mock_passage_map_invalid()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * 13);
	map->map[0] =  ft_strdup("111111111111111");
	map->map[1] =  ft_strdup("100000000000001");
	map->map[2] =  ft_strdup("100000000000001");
	map->map[3] =  ft_strdup("100000000000001");
	map->map[4] =  ft_strdup("100000000000001");
	map->map[5] =  ft_strdup("100000000100011");
	map->map[6] =  ft_strdup("100000000000001");
	map->map[7] =  ft_strdup("100000000000001");
	map->map[8] =  ft_strdup("1000000000W0001");
	map->map[9] =  ft_strdup("111111111111111");
	map->map[10] = ft_strdup("111110000001111");
	map->map[11] = ft_strdup("11111 1111 1111");
	map->map[12] = NULL;
	return (map);
}

t_map	*mock_deep_passage_map_invalid()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * 13);
	map->map[0] =  ft_strdup("111111111111111");
	map->map[1] =  ft_strdup("100000000000001");
	map->map[2] =  ft_strdup("100000000000001");
	map->map[3] =  ft_strdup("100000000000001");
	map->map[4] =  ft_strdup("100000000000001");
	map->map[5] =  ft_strdup("100000000100011");
	map->map[6] =  ft_strdup("100000000000001");
	map->map[7] =  ft_strdup("100000000000001");
	map->map[8] =  ft_strdup("10000 0000W0001");
	map->map[9] =  ft_strdup("11111 111111111");
	map->map[10] = ft_strdup("11111 000001111");
	map->map[11] = ft_strdup("11111 1111 1111");
	map->map[12] = NULL;
	return (map);
}

t_map	*mock_deep_passage_map_valid()
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->map = malloc(sizeof(char *) * 13);
	map->map[0] =  ft_strdup("111111111111111");
	map->map[1] =  ft_strdup("100000000000001");
	map->map[2] =  ft_strdup("100000000000001");
	map->map[3] =  ft_strdup("100000000000001");
	map->map[4] =  ft_strdup("100000000000001");
	map->map[5] =  ft_strdup("100000000100011");
	map->map[6] =  ft_strdup("100000000000001");
	map->map[7] =  ft_strdup("100000000000001");
	map->map[8] =  ft_strdup("1000010000W0001");
	map->map[9] =  ft_strdup("11111 111111111");
	map->map[10] = ft_strdup("11111 100001111");
	map->map[11] = ft_strdup("11111 1111 1111");
	map->map[12] = NULL;
	return (map);
}

void	test_with_mocks()
{
	int	i;
	char	*passed;
	char	*failed;

	passed = "\033[0;32mPASSED\033[0m";
	failed = "\033[1;31m FAILED \033[0m";
	void	*valid_mocks[] = {
		&mock_map_shifted_section_valid,
		&mock_base_map_valid,
		mock_passage_map_valid,
		mock_deep_passage_map_valid,
		NULL
	};

	void	*invalid_mocks[] = {
		&mock_map_with_spaces_invalid,
		&mock_map_shifted_section_invalid,
		mock_passage_map_invalid,
		mock_deep_passage_map_invalid,
		NULL
	};

	ft_printf("\033[0;32m Testing valid maps::::\n\033[0m");
	i = 0;
	while (valid_mocks[i])
	{
		t_map	*map;
		map = ((t_map *(*)(void))valid_mocks[i])();
		int	result;
		result = validate(map);
		t_position player_position = get_player_position(map);
		ft_printf("Player position: %d, %d, %s\n", player_position.x, player_position.y, direction_to_str(player_position.direction));
		if (result == 1)
		{
			ft_printf("Test case %s for map %d\n", passed, i);
			ft_printf("Map is valid\n");
		}
		else
			ft_printf("Test case %s for map %d\n", failed, i);
		i++;
	}
	ft_printf("--------------------\n");
	ft_printf("\033[0;32m Testing invalid maps::::\n\033[0m");
	i = 0;
	while (invalid_mocks[i])
	{
		t_map	*map;
		map = ((t_map *(*)(void))invalid_mocks[i])();
		int	result;
		result = validate(map);
		t_position player_position = get_player_position(map);
		ft_printf("Player position: %d, %d, %s\n", player_position.x, player_position.y, direction_to_str(player_position.direction));
		if (result == 0)
		{
			ft_printf("Test case %s for map %d\n", passed, i);
			ft_printf("Map is invalid\n");
		}
		else
			ft_printf("Test case %s for map %d\n", failed, i);
		i++;
	}
	ft_printf("END OF MOCKS\n");
	ft_printf("--------------------\n");
}
