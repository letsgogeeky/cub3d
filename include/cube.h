#ifndef CUBE_H
# define CUBE_H

# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "MLX42/MLX42.h"
# include "baselib.h"
# include <stdbool.h>

# define WIDTH 1366
# define HEIGHT 768

enum e_symbol
{
	EMPTY = ' ',
	WALL = '1',
	SPACE = '0',
};

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
	char	*str_color;
	int		red;
	int		green;
	int		blue;
}		t_color;

typedef struct s_map // every element is allocated and has to be freed if failure occures
{
	t_texture	*north_texture;
	t_texture	*south_texture;
	t_texture	*west_texture;
	t_texture	*east_texture;
	t_color		*floor_color;
	t_color		*ceiling_color;
	char				**map;
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

int			largest_of_three(int a, int b, int c);
bool		valid_with_surrounding(char *line, char *prev, char *next, char ignore);
bool		surrounded_by_wall(char *line, char ignore);
int			validate(t_map *map);
t_position	get_player_position(t_map *map);
char		*direction_to_str(enum e_direction direction);
void		test_with_mocks();
t_game	*init_game(void);


//map_init.c
t_map	*parse(t_map *m, int fd, char *argv);
int		parse_map(int fd, t_map *m, char *tmp, char *argv);
int		fill_map(t_map *m, int fd, int rows, int max_length);
void	set_char(int i, char *tmp, int max_length, t_map *m);

//test.c
void	test_parsing(t_map *m, int rows);
void	test_wall(t_map *m);

//wall_init.c
void	fill_var_map(int flag, char *ptr, t_map *m);
void	set_var_map(t_map *m, char *ptr);
void	free_walls(t_map *m);
char	*parse_walls(int fd, t_map *m);

//init_helpers.c
void	ft_prerr(char *str, char *argv);
int		zero_map_struct(t_map *m);
void	free_map_struct(t_map *m);
int		set_max_len(char *str, int max);
int		find_start_map(char *str);
int		check_all_arg(t_map *m);
void	free_map_struct2(t_map *m);

#endif