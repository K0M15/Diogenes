.PHONY = clean fclean re


PATH_LIBFT = libft/libft.a
FLAGS =-Wall -Wextra -Werror 
FLAGS +=-g -fsanitize=address
NAME = philosophers
#	CORE
FILES += philosophers.c
FILES += args.c chronos.c runtime.c fork.c
FILES += observer.c philo_impl.c philo_object.c
FILES += shared.c

CC=cc

all: $(NAME)
	

$(NAME): $(PATH_LIBFT) $(FILES:.c=.o) 
	@echo "\033[32mBuilding executable\033[0m"
	$(CC) $(FILES:.c=.o) -o $(NAME) $(FLAGS) $(PATH_LIBFT) -Iinclude

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $^

clean:
	@echo "\033[31mDeleting Objects\033[0m"
	make -C libft clean
	rm -f $(FILES:.c=.o)

$(PATH_LIBFT):
	@echo "\033[32mBuilding Libft\033[0m"
	@make -C libft bonus

fclean: clean
	@echo "\033[31mDeleting executable\033[0m"
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
