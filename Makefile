
NAME:= cub3d

BASELIB := ./lib/ft-baselib
LIBMLX := ./lib/MLX42
CFLAGS	:= -Wextra -Wall -Werror -g -funroll-loops -march=native -flto -ffast-math -fsanitize=address
LDFLAGS := -ldl -lglfw -pthread -lm -fsanitize=address -flto -framework Cocoa -framework OpenGL -framework IOKit
HEADERS := -I ./include -I ${BASELIB}/include -I $(LIBMLX)/include

SRC_PARSER := parser/validator.c parser/map_init.c
SRC_MAIN := main.c
SRCS := $(SRC_MAIN) $(SRC_PARSER)

OBJS := ${addprefix src/, ${SRCS:.c=.o}}
LIBS := $(LIBMLX)/build/libmlx42.a ${BASELIB}/baselib.a

all: MLX BASELIB ${NAME}

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

${NAME}: $(LIBS) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(LDFLAGS) -o $(NAME) && echo "Successful $(NAME) build...!"

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

fclean: clean
	@$(MAKE) fclean --directory=${BASELIB}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
