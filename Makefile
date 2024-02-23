
NAME:= cub3d

BASELIB := ./lib/ft-baselib
CFLAGS	:= -Wextra -Wall -Werror -g
HEADERS := -I ./include -I ${BASELIB}/include

SRC_PARSER := parser/validator.c parser/map_init.c
SRC_MAIN := main.c
SRCS := $(SRC_MAIN) $(SRC_PARSER)

OBJS := ${addprefix src/, ${SRCS:.c=.o}}
LIBS := ${BASELIB}/baselib.a

all: BASELIB ${NAME}

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $<

${NAME}: $(LIBS) $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) && echo "Successful $(NAME) build...!"

BASELIB:
	@if [ -d ${BASELIB} ]; then\
		echo "${BASELIB} already exists... proceeding to next step.";\
	else\
		mkdir lib;\
		git clone git@github.com:letsgogeeky/ft-baselib.git ${BASELIB};\
	fi
	make --directory=${BASELIB}

debug: 
	@$(MAKE) CFLAGS="-Wextra -Wall -Werror -g -D LOG_DETAILS=1" re

clean:
	@rm -rf $(OBJS)

fclean: clean
	@$(MAKE) fclean --directory=${BASELIB}
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
