#include "fdf.h"

void	my_mlx_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;
	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ; 
	dst = map->addr + (y * map->line_length + x * (map->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	key_handler(int keycode, t_map *map)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(map->mlx, map->mlx_win);
		exit(0);
	}
	return (0);
}

int	close_handler(t_map *map)
{
	mlx_destroy_window(map->mlx, map->mlx_win);
	exit(0);
	return (0);
}

void	get_scale(t_map *map)
{
	float	scale_x;
	float	scale_y;
	int		max_z;

	max_z = get_max_z(map);
	scale_x = (float)WINDOW_WIDTH / (map->width * 2);
	scale_y = (float)WINDOW_HEIGHT / (map->height * 2 + max_z);
	if (scale_x < scale_y)
		map->scale = scale_x;
	else
		map->scale = scale_y;
}

int get_max_z(t_map *map)
{
	int	y;
	int	x;
	int	max;

	max = map->values[0][0];
	for (y = 0; y < map->height; y++)
		for (x = 0; x < map->width; x++)
			if (map->values[y][x] > max)
				max = map->values[y][x];
	return (max);
}
