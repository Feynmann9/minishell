NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

FILES = $(wildcard sources/*.c) \
		$(wildcard libft/*.c)

OBJ = $(FILES:.c=.o)

%.o: $(FILES)/%.c
		$(CC) -c $< -o $@

$(NAME): $(OBJ)
		$(CC) -o $(NAME) $(OBJ)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re