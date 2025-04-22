.PHONY: all clean fclean re objects objects_bonus bonus norm

NAME=libft.a
FILES=		ft_atoi.o \
			ft_bzero.o \
			ft_calloc.o \
			ft_isalpha.o \
			ft_isdigit.o \
			ft_isalnum.o \
			ft_isascii.o \
			ft_isprint.o \
			ft_toupper.o \
			ft_tolower.o \
			ft_itoa.o \
			ft_memcmp.o \
			ft_memset.o \
			ft_memcpy.o \
			ft_memmove.o \
			ft_memchr.o \
			ft_putchar_fd.o \
			ft_putstr_fd.o \
			ft_putendl_fd.o \
			ft_putnbr_fd.o \
			ft_split.o \
			ft_strlcat.o \
			ft_strlcpy.o \
			ft_strlen.o \
			ft_strchr.o \
			ft_strrchr.o \
			ft_strncmp.o \
			ft_strnstr.o \
			ft_striteri.o \
			ft_strmapi.o \
			ft_strtrim.o \
			ft_strdup.o \
			ft_substr.o \
			ft_strjoin.o \
			ft_striteri.o \
			ft_strmapi.o \
			ft_strtrim.o \

BONUS_FILES=ft_lstnew_bonus.o \
			ft_lstadd_front_bonus.o \
			ft_lstsize_bonus.o \
			ft_lstlast_bonus.o \
			ft_lstadd_back_bonus.o \
			ft_lstdelone_bonus.o \
			ft_lstclear_bonus.o \
			ft_lstiter_bonus.o \
			ft_lstmap_bonus.o

PRINTF_FILES=	ft_printf.o\
				ft_write_char.o \
				ft_write_hex.o \
				ft_write_number.o \
				ft_write_ptr.o \
				ft_write_string.o

GNL_FILES = get_next_line_utils.o \
			get_next_line.o

SOURCE=$(FILES:.o=.c)
BONUS_SOURCE=$(BONUS_FILES:.o=.c)
PRINTF_SOURCE=$(PRINTF_FILES:.o=.c)
GNL_SOURCE=$(GNL_FILES:.o=.c)

CFLAGS=-Wall -Wextra -Werror
CC=cc


all: bonus

$(NAME): $(FILES) $(PRINTF_FILES) $(GNL_FILES)
	@ar -crs $(NAME) $(FILES) $(PRINTF_FILES) $(GNL_FILES)

clean:
	@rm -f $(FILES)
	@rm -f $(PRINTF_FILES)
	@rm -f $(BONUS_FILES)
	@rm -f $(GNL_FILES)

fclean: clean
	@rm -f libft.a

re: fclean all

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $^ -I../include

bonus: $(FILES) $(BONUS_FILES) $(NAME) $(PRINTF_FILES) $(GNL_FILES)
	@ar -crs $(NAME) $(FILES) $(BONUS_FILES) $(PRINTF_FILES) $(GNL_FILES)

norm:
	norminette $(SOURCE) $(BONUS_SOURCE) $(PRINTF_SOURCE) $(GNL_FILES)
