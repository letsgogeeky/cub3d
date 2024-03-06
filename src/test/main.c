#include "testcub.h"

# define PASSED "\033[0;32mPASSED\033[0m"
# define FAILED "\033[1;31m FAILED \033[0m"

void	test_valid()
{
	int	i;
	void	*valid_mocks[] = {
		&mock_map_shifted_section_valid,
		&mock_base_map_valid,
		mock_passage_map_valid,
		mock_deep_passage_map_valid,
		NULL
	};

	i = -1;
	while (valid_mocks[++i])
	{
		t_map	*map;
		map = ((t_map *(*)(void))valid_mocks[i])();
		int	result;
		result = validate(map);
		log_player_position(map);
		if (result == 1)
			ft_printf("Test case %s for map %d\n", PASSED, i);
		else
			ft_printf("Test case %s for map %d\n", FAILED, i);
	}
}
void	test_invalid()
{
	int	i;

	void	*invalid_mocks[] = {
		&mock_map_with_spaces_invalid,
		&mock_map_shifted_section_invalid,
		mock_passage_map_invalid,
		mock_deep_passage_map_invalid,
		NULL
	};

	i = -1;
	while (invalid_mocks[++i])
	{
		t_map	*map;
		map = ((t_map *(*)(void))invalid_mocks[i])();
		int	result;
		result = validate(map);
		log_player_position(map);
		if (result == 0)
			ft_printf("Test case %s for map %d\n", PASSED, i);
		else
			ft_printf("Test case %s for map %d\n", FAILED, i);
	}
}

int	main(int ac, char **argv)
{
	(void)ac;
	(void)argv;
	ft_printf("\033[0;32m Testing valid maps::::\n\033[0m");
	test_valid();
	ft_printf("--------------------\n");
	test_invalid();
	ft_printf("\033[0;32m Testing invalid maps::::\n\033[0m");
	ft_printf("END OF MOCKS\n");
	ft_printf("--------------------\n");
	return (0);
}
