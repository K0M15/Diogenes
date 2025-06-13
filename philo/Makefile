CC=cc
FILES= main.c ft_mutex.c observer.c philosopher.c speaker.c input.c
NAME=philosopher
FLAGS = -Wall -Wextra -Werror
FLAGS += -g -gdwarf-2 #-fsanitize=address
OBJ_DIR = objects

OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(FILES))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_FILES)
	@echo "Building $(NAME)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ_FILES)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "Building $@"
	@$(CC) $(FLAGS) -c -o $@ $< 

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all
