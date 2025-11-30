NAME = pipex
CFLAGS = -Wall -Wextra -Werror
CC = cc

SRCS := pipex.c ft_memcpy.c ft_strclear.c ft_strjoin.c\
ft_strlen.c ft_strncmp.c ft_substr.c ft_split.c\
get_next_line_utils.c get_next_line.c ft_close_prev_while.c\
ft_close_on_while.c ft_creat_first_child.c ft_creat_middle_childs.c\
ft_creat_last_child.c ft_get_path.c ft_utils.c ft_here_doc.c

OBJS := ${SRCS:.c=.o}

HEADER := pipex.h

all: ${NAME}

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
