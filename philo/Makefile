.PHONY = clean fclean re

OBJ_DIR = objects

PATH_LIBFT = libft/libft.a
FLAGS =-Wall -Wextra -Werror 
FLAGS +=-g -fsanitize=address
NAME = philosophers
#	CORE
# FILES += philosophers.c
FILES += args.c chronos.c runtime.c fork.c
FILES += observer.c philo_impl.c philo_object.c
FILES += shared.c

OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(FILES))
CC=cc

all: $(NAME)

lifetest: $(PATH_LIBFT) $(OBJ_DIR) $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(PATH_LIBFT) $(FLAGS) lifecycle_philo_test.c -o life_test -Iinclude

$(NAME): $(PATH_LIBFT) $(OBJ_DIR) $(OBJ_FILES) 
	@echo "\033[32mBuilding executable\033[0m"
	$(CC) $(OBJ_FILES) -o $(NAME) philosophers.c $(FLAGS) $(PATH_LIBFT) -Iinclude

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "CREATING" $@
	@$(CC) $(FLAGS) -c -o $@ $^ -Iinclude

$(OBJ_DIR):
	@echo "\033[32mCreating Object Folder...\033[0m"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "\033[31mDeleting Objects\033[0m"
	@make -C libft clean
	@rm -rf $(OBJ_DIR)
	@rm -f $(FILES:.c=.o)

$(PATH_LIBFT):
	@echo "\033[32mBuilding Libft\033[0m"
	@make -C libft bonus

fclean: clean
	@echo "\033[31mDeleting executable\033[0m"
	@make -C libft fclean
	@rm -f $(NAME)

re: fclean all
