#ifndef CUBE_H
# define CUBE_H

# include "baselib.h"
# include <stdbool.h>

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
}		t_map;

int		validate(t_map *map);
t_map	*mock_map_with_spaces_invalid();
t_map	*mock_base_map_valid();
t_map	*mock_map_shifted_section_valid();
t_map	*mock_map_shifted_section_invalid();

#endif