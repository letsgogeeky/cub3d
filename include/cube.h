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

# define STRUCT_FAILED "building of struct failed"
# define INV_MAP "invalid map"
# define PARSING_MAP_FAILED "parsing of the input map failed"
# define INV_FD "invalid file descriptor"
# define PARSING_FAILED "parsing failed"
# define WRONG_ARG "wrong amount of arguments entered"
# define CUB_FORMAT "input file needs .cub format"
# define INV_TEX_FILE "texture file included in map is invalid"
# define FAIL_GAME_INIT "Error: failed to initialize game\n"

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

typedef struct  s_vector
{
    float   x;
    float   y;
}       t_vector;

typedef struct	s_vector_int
{
	int		x;
	int		y;
}		t_vector_int;

typedef struct s_position
{
    int                 x;
    int                 y;
    // enum e_direction start_orientation;
    t_vector            direction;
}       t_position;

typedef struct s_ray // size of arrays equals amnt of rays
{
    // int                  amnt_of_rays; //for every x (or y if steep wall)
    int			        hit_x; //calculate by myself
	int			        hit_y; //calculate by myself
    t_vector            ray; // has to be from position to hitpoint so that i can calculate the rest
	t_vector			angle;
	t_vector			side_dist;
	t_vector			delta_dist;
    int                 len_to_wall; //calculate by myself
    int                 wall_height; //calculate by myself
    enum e_direction    wall_texture;
}       t_ray;

typedef struct s_texture
{
	char			*path;
	mlx_texture_t	*tex;
}		t_texture;

typedef struct	s_player
{
	t_position	pos;
	t_vector	dir;
	t_vector	plane;
	double		rotation_angle;
	double		walk_speed;
	double		turn_speed;

}		t_player;

typedef struct s_data
{
    t_player  	player;
    t_ray       *rays;
}       t_data;

typedef struct s_color
{
	char	*str_color;
	int		red;
	int		green;
	int		blue;
	int		hex_color_rgb;
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
	mlx_t		*mlx;
}		t_graphics;

typedef struct s_game
{
	// TODO: move graphics attrs to this struct and remove the graphics struct
	t_map		*map;
	t_graphics	*graphics;
	t_data      *data;
}		t_game;

int			validate(t_map *map);
t_position	get_player_position(t_map *map);
void		log_player_position(t_map *map);
char		*direction_to_str(enum e_direction direction);

//init.c
t_game		*allocate_game(t_map *m);
t_game		*init_game(t_map *m);
// void		ft_keyhook(mlx_key_data_t keydata, void *param);
void		ft_hook(void *param);
void		free_game(t_game *game);
void		open_n_draw(t_map *m);

//map_init.c
void		set_char(int i, char *tmp, int max_length, t_map *m);
int			fill_map(t_map *m, int fd, int rows, int max_length);
int			parse_map(int fd, t_map *m, char *tmp, char *argv);
t_map		*parse(t_map *m, int fd, char *argv);

//wall_init.c
void		fill_var_map(int flag, char *ptr, t_map *m);
void		set_var_map(t_map *m, char *ptr);
int			fill_color_struct(t_color *c);
void		adjust_wall_path(t_map *m);
char		*parse_walls(int fd, t_map *m);

//init_helpers.c
void		ft_prerr(char *str, char *argv);
int			zero_map_struct(t_map *m);
int			set_max_len(char *str, int max);
int			find_start_map(char *str);
int			colorcode(int red, int green, int blue);

//free.c
void		free_s_texture(t_texture *t);
void		free_string(char *str);
void		free_color(t_color *c);
void		free_walls(t_map *m);
void		free_map_struct(t_map *m);
void		free_game(t_game *game);

//check.c
void		check_n_change_c(char *str);
int			check_end(char *str);
int			check_path(t_map *m);
int			check_all_arg(t_map *m);

//test.c
void		test_parsing(t_map *m, int rows);
void		test_wall(t_map *m);

//draw.c
void		fill_block(t_game *game, int block_size, int x, int y, int color);
void		draw_vert(t_game *game, int block_size);
void		draw_hor(t_game *game, int block_size);
void		draw_block(t_game *game);

#endif