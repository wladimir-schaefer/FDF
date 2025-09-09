#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h> 
# include <fcntl.h>

typedef struct s_map
{
	int **values;
	int width;
	int height;
}	t_map;


int		main(int argc, char **argv);
void	error(t_map *map, char *error_message);
void	error_str(char *str, char *error_message);
void	error_split(t_map *map, char **split);
t_map	*get_map(char *file);
void	get_dimensions(t_map *map, char *file);
void	allocate_array(t_map *map);
void	fill_array(t_map *map,char *file);
int		*char_arr_to_int_arr(char **split, int width);
size_t	count_tokens(char **str);
size_t	count_tokens_in_string(char const *w, char c);
int	check_tokens(t_map *map, int tokens);
void	free_split(char **split);
void	free_map(t_map *map);
char	*ft_strtrim(char const *s1, char const *set);


#endif