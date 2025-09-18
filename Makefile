NAME    = fdf
SRC     = main.c get_map.c get_map_utils.c get_map_utils_2.c \
          draw.c draw_utils.c draw_line.c
OBJ     = $(SRC:.c=.o)

# Paths
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Compiler & flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I$(LIBFT_DIR) -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean re
