#ifndef CUBE_H
# define CUBE_H

# include "baselib.h"

typedef struct s_texture
{
	char	*path;
}		t_texture;

typedef struct s_color
{
	char	*str_color;
	int		red;
	int		green;
	int		blue;
}		t_color;

typedef struct s_map // every element is allocated and has to be freed if failure occures
{
	struct t_texture	*north_texture;
	struct t_texture	*south_texture;
	struct t_texture	*west_texture;
	struct t_texture	*east_texture;
	struct t_color		*floor_color;
	struct t_color		*ceiling_color;
	char 				**map;
}		t_map;

#endif