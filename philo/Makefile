.PHONY = clean fclean re


PATH_LIBFT = libft/libft.a
FLAGS =-Wall -Wextra -Werror 
FLAGS +=-g -fsanitize=address
NAME = philosophers
#	CORE
FILES += philosophers.c
FILES += args.c runtime.c
CC=cc


all: $(NAME)
	

$(NAME): $(PATH_LIBFT) $(FILES:.c=.o) 
	$(CC) $(FILES:.c=.o) -o $(NAME) $(FLAGS) $(PATH_LIBFT) -Iinclude

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^

clean:
	rm -f $(FILES:.c=.o)

$(PATH_LIBFT):
	@make -C libft bonus

fclean: clean
	rm -f $(NAME)

re: fclean all
