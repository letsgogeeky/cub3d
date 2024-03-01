#ifndef CUBE_H
# define CUBE_H

# include "baselib.h"
# include <stdbool.h>

enum e_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
};

typedef struct s_position
{
	int					x;
	int					y;
	enum e_direction	direction;
}		t_position;
typedef struct s_texture
{
	char	*path;
}		t_texture;

typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
}		t_color;

typedef struct s_map
{
	struct t_texture	*north_texture;
	struct t_texture	*south_texture;
	struct t_texture	*west_texture;
	struct t_texture	*east_texture;
	struct t_color		*floor_color;
	struct t_color		*ceiling_color;
	char 				**map;
	int					rows;
	int					cols;
}		t_map;

int		validate(t_map *map);
void	test_with_mocks();

#endif