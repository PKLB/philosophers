CC= gcc
CFLAGS= -Wall -Wextra -Werror
RM=rm -f
NAME=philosophers
SRCS= main.c \
	  checks.c \
	  error.c \
	  utils.c \
	  parsing.c \
	  start.c \
	  get_time.c


OBJS=${SRCS:.c=.o}

all:	${NAME}

${NAME}:	${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re