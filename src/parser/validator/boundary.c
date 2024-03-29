#include "validator.h"

int	index_of_nonignore(char *line, char ignore, bool from_front)
{
	int	i;

	if (from_front)
	{
		i = 0;
		while (line[i] == ignore)
			i++;
	}
	else
	{
		i = ft_strlen(line) - 1;
		while (line[i] == ignore)
			i--;
	}
	return (i);
}

bool	valid_from_back(char *line, char *prev, char *next, char ignore)
{
	int	i;
	int	prev_i;
	int	next_i;
	int	smallest;

	i = index_of_nonignore(line, ignore, false);
	prev_i = index_of_nonignore(prev, ignore, false);
	next_i = index_of_nonignore(next, ignore, false);
	smallest = smallest_of_three(i, prev_i, next_i);
	while (line[i] && i > smallest)
	{
		if (line[i] != WALL)
			return (false);
		i--;
	}
	return (true);
}

bool	valid_from_front(char *line, char *prev, char *next, char ignore)
{
	int	i;
	int	prev_i;
	int	next_i;
	int	largest;

	i = index_of_nonignore(line, ignore, true);
	prev_i = index_of_nonignore(prev, ignore, true);
	next_i = index_of_nonignore(next, ignore, true);
	largest = largest_of_three(i, prev_i, next_i);
	while (line[i] && i < largest)
	{
		if (line[i] != WALL)
			return (false);
		i++;
	}
	return (true);
}

bool	valid_with_surrounding(char *line, char *prev, char *next, char ignore)
{
	if (!valid_from_front(line, prev, next, ignore))
		return (printf("Failed on line: %s from front\n", line), false);
	if (!valid_from_back(line, prev, next, ignore))
		return (printf("Failed on line: %s from back\n", line), false);
	return (true);
}

bool	surrounded_by_wall(char *line, char ignore)
{
	int	i;

	i = index_of_nonignore(line, ignore, true);
	if (line[i] != WALL)
		return (false);
	i = index_of_nonignore(line, ignore, false);
	if (line[i] != WALL)
		return (false);
	return (true);
}
