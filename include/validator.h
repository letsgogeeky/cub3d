#ifndef VALIDATOR_H
# define VALIDATOR_H

# include "cube.h"

int			smallest_of_three(int a, int b, int c);
int			largest_of_three(int a, int b, int c);
bool		is_empty(char *row);
bool		valid_with_surrounding(char *line, char *prev, \
				char *next, char ignore);
bool		surrounded_by_wall(char *line, char ignore);

#endif