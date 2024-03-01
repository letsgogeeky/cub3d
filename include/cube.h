#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "MLX42/MLX42.h"

# define WIDTH 1366
# define HEIGHT 768

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

t_game	*init_game(void);

#endif