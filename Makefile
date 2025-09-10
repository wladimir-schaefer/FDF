NAME    = fdf
SRC     = get_map.c get_map_utils.c fdf.c
OBJ     = $(SRC:.c=.o)

# Paths
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Compiler & flags
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g -I$(MLX_DIR) -I$(LIBFT_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
	$(CC) $(OBJ) $(LIBFT_LIB) $(LDFLAGS) -o $(NAME)
#	@rm -f $(OBJ)   # remove object files right after linking

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(MLX_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: clean fclean re
