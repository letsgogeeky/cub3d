
NAME:= cub3D
NAME_TEST:= test

BASELIB := ./lib/ft-baselib
LIBMLX := ./lib/MLX42
CFLAGS	:= -Wextra -Wall -Werror -g -fsanitize=address -funroll-loops -march=native -flto -ffast-math
LDFLAGS := -ldl -lglfw -pthread -lm -fsanitize=address -flto -framework Cocoa -framework OpenGL -framework IOKit
HEADERS := -I ./include -I ${BASELIB}/include -I $(LIBMLX)/include

SRC_PARSER := parser/validator/validator.c parser/validator/boundary.c parser/validator/utils.c \
			parser/map_init.c parser/check.c \
			parser/free.c parser/init_helpers.c parser/wall_init.c \
			parser/validator/passages.c parser/allocate.c

SRC_ENGINE := engine/caster/cast.c engine/caster/draw_2d.c engine/movement.c \
			engine/caster/set_var.c engine/caster/calc_ray.c engine/caster/check_ray.c \
			engine/player/player.c engine/player/utils.c engine/player/utils_2.c engine/caster/image.c \
			engine/caster/draw_3d.c engine/caster/calc_3d.c engine/caster/set_var_2.c \
      		engine/door.c engine/math_utils.c engine/texture.c \
			engine/minimap/draw.c engine/minimap/paint.c

SRC_GRAPHICS := graphics/hooks.c graphics/utils.c

SRCS := $(SRC_PARSER) $(SRC_ENGINE) $(SRC_GRAPHICS)
SRC_MAIN := main.c init.c cleanup.c

OBJS := ${addprefix src/, ${SRCS:.c=.o} ${SRC_MAIN:.c=.o}}
OBJS_TEST := ${addprefix src/, ${SRCS:.c=.o} ${SRC_TEST:.c=.o}}
LIBS := $(LIBMLX)/build/libmlx42.a ${BASELIB}/baselib.a

all: MLX BASELIB ${NAME}

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

${NAME}: $(LIBS) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LDFLAGS) -o $(NAME) && echo "Successful $(NAME) build...!"

${NAME_TEST}: MLX BASELIB $(LIBS) $(OBJS_TEST)
	@$(CC) $(OBJS_TEST) $(LIBS) $(HEADERS) $(LDFLAGS) -o $(NAME_TEST) && echo "Successful $(NAME_TEST) build...!"
	./test

BASELIB:
	@if [ -d ${BASELIB} ]; then\
		echo "${BASELIB} already exists... proceeding to next step.";\
	else\
		mkdir lib;\
		git clone git@github.com:letsgogeeky/ft-baselib.git ${BASELIB};\
	fi
	make --directory=${BASELIB}

MLX:
	@if [ -d ${LIBMLX} ]; then\
		echo "${LIBMLX} already exists... proceeding to next step.";\
	else\
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX);\
		cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4;\
	fi

rmlibs:
	rm -rf lib/MLX42
	rm -rf lib/ft-baselib

clean:
	@rm -rf $(OBJS)
	@rm -rf $(OBJS_TEST)

fclean: clean
	rm -f ${NAME}
	rm -f ${NAME_TEST}

relib: rmlibs MLX BASELIB

libclean:
	@$(MAKE) fclean --directory=${BASELIB}

re: fclean all

.PHONY: all clean fclean re
