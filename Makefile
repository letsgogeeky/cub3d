
NAME:= cub3d
NAME_TEST:= test

BASELIB := ./lib/ft-baselib
LIBMLX := ./lib/MLX42
CFLAGS	:= -Wextra -Wall -Werror -g -fsanitize=address #-funroll-loops -march=native -flto -ffast-math
LDFLAGS := -ldl -lglfw -pthread -lm -fsanitize=address -flto -framework Cocoa -framework OpenGL -framework IOKit
HEADERS := -I ./include -I ${BASELIB}/include -I $(LIBMLX)/include

SRC_TEST := test/invalid_mocks.c test/valid_mocks.c test/main.c

SRC_PARSER := parser/validator/validator.c parser/validator/boundary.c parser/validator/utils.c \
			parser/map_init.c parser/player.c parser/check.c parser/test.c \
			parser/free.c parser/init_helpers.c parser/wall_init.c 

SRC_ENGINE := engine/caster/cast.c
SRCS := $(SRC_PARSER) $(SRC_ENGINE)
SRC_MAIN := main.c init.c draw.c

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
	@$(MAKE) fclean --directory=${BASELIB}
	rm -f ${NAME}
	rm -f ${NAME_TEST}

re: fclean all

.PHONY: all clean fclean re
