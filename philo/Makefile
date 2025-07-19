
CC=cc
FILES= main.c ft_mutex.c observer.c philosopher.c speaker.c input.c
FILES+= time.c message.c ft_mutex_id.c
NAME=philo
FLAGS = -Wall -Wextra -Werror
FLAGS += -g #-gdwarf-2 
# FLAGS += -fsanitize=address
OBJ_DIR = objects

.PHONY: clean fclean all re

OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(FILES))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_FILES)
	@echo "Building $(NAME)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Building $@"
	@$(CC) $(FLAGS) -c -o $@ $< 

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Deleting Objects"

fclean: clean
	@rm -f $(NAME)
	@echo "Deleting Executable"

re: fclean all
