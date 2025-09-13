/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:17:32 by wschafer          #+#    #+#             */
/*   Updated: 2025/09/13 15:56:50 by wschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# include "mlx.h"
# include "libft/libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h> 
# include <fcntl.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define COLOR 0xFFFFFF

typedef struct s_map
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		**values;
	int		width;
	int		height;
	float	scale;

}	t_map;

typedef struct s_point2d
{
	int x;
	int y;
}	t_point2d;

int		main(int argc, char **argv);
void	draw(t_map *map);
void	error(t_map *map, char *error_message);
void	error_str(char *str, char *error_message);
void	error_split(t_map *map, char **split);
t_map	*get_map(char *file);
void	get_dimensions(t_map *map, char *file);
void	allocate_array(t_map *map);
void	fill_array(t_map *map, char *file);
int		*char_arr_to_int_arr(char **split, int width);
size_t	count_tokens(char **str);
size_t	count_tokens_in_string(char const *w, char c);
int		check_tokens(t_map *map, int tokens);
void	free_split(char **split);
void	free_map(t_map *map);
char	*ft_strtrim(char const *s1, char const *set);
void	my_mlx_pixel_put(t_map *map, int x, int y, int color);
int		key_handler(int keycode, t_map *map);
int		close_handler(t_map *map);

// draw_line.c
void	draw_line(t_map *map, t_point2d p1, t_point2d p2, int color);
void	update_err_and_step(int *err, int dx, int dy, t_point2d *p, int sx, int sy);
int		get_step(int a, int b);

#endif