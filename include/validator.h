#ifndef VALIDATOR_H
# define VALIDATOR_H

# include "cube.h"

int			smallest_of_three(int a, int b, int c);
int			largest_of_three(int a, int b, int c);
bool		is_empty(char *row);
int			index_of_nonignore(char *line, char ignore, bool from_front);
bool		valid_with_surrounding(char *line, char *prev, \
				char *next, char ignore);
bool		surrounded_by_wall(char *line, char ignore);
bool 		validate_bottom_top_passages(t_map *map);
bool		validate_top_bottom_passages(t_map *map);
bool		all_ones(char *line, bool allow_empty);

#endif