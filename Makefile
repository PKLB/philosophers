CC= gcc
CFLAGS= -Wall -Wextra -Werror -Ofast
RM=rm -f
NAME=philosophers
SRCS= main.c \
	  checks.c \
	  error.c \
	  utils.c \
	  parsing.c \
	  get_time.c \
	  threads.c \
	  prints.c


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