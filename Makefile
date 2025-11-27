NAME = pipex
CFLAGS = -g -Wall -Wextra -Werror
CC = cc

SRCS := poulet.c ft_memcpy.c ft_strclear.c ft_strjoin.c\
ft_strlen.c ft_strncmp.c ft_substr.c utils.c ft_split.c get_next_line_utils.c get_next_line.c
OBJS := ${SRCS:.c=.o}

HEADER := poulet.h

all: ${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
