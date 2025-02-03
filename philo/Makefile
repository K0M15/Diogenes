.PHONY = clean fclean re

FLAGS =-Wall -Wextra -Werror 
FLAGS +=-g -fsanitize=address
NAME = push_swap
#	CORE
FILES += 
CC=cc


all: $(NAME)
	

$(NAME): $(FILES:.c=.o)
	$(CC) $(FILES:.c=.o) -o $(NAME) $(FLAGS)

%.o: %.c
	$(CC) $(FLAGS) -c -o $@ $^

clean:
	rm -f $(FILES:.c=.o)

fclean: clean
	rm -f $(NAME)

re: fclean all
