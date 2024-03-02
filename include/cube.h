#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "MLX42/MLX42.h"
# include "baselib.h"
# include <stdbool.h>

# define WIDTH 1366
# define HEIGHT 768

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

typedef struct s_graphics
{
	mlx_image_t	*image;
	void		*mlx;
	int			width;
	int			height;
}		t_graphics;

typedef struct s_game
{
	t_map		*map;
	t_graphics	*graphics;
}		t_game;


int			validate(t_map *map);
t_position	get_player_position(t_map *map);
char		*direction_to_str(enum e_direction direction);
void		test_with_mocks();
t_game	*init_game(void);

#endif