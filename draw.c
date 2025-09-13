#include "fdf.h"

void	draw(t_map *map)
{
	map->mlx = mlx_init();
	map->mlx_win = mlx_new_window(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	map->img = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	map->addr = mlx_get_data_addr(map->img, &map->bits_per_pixel, &map->line_length,
								&map->endian);
	my_mlx_pixel_put(map, 100, 100, 0x00FF0000);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img, 0, 0);
	mlx_key_hook(map->mlx_win, key_handler, map);
	mlx_hook(map->mlx_win, 17, 0, close_handler, map);
	mlx_loop(map->mlx);
}

void	*get_two_dim_point(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			handle_point(map, x, y);
			x++;
		}
		y++;
	}
}

void	handle_point(t_map *map, int x, int y)
{
	t_point2d p1;
	t_point2d p2;

	p1 = project_point(map, x, y, map->values[y][x]);
	if (x < map->width - 1)
	{
		p2 = project_point(map, x + 1, y, map->values[y][x + 1]);
		draw_line(map, p1, p2, COLOR);
	}
	if (y < map->height - 1)
	{
		p2 = project_point(map, x, y + 1, map->values[y + 1][x]);
		draw_line(map, p1, p2, COLOR);
	}
}


t_point2d	project_point(t_map *map, int x, int y, int z)
{
	t_point2d	p;
	float		iso_x;
	float		iso_y;
	
	get_scale(map);
	iso_x = (x  * map->scale- y * map->scale) * cos(30 * M_PI / 180);
	iso_y = (x * map->scale + y * map->scale) * sin(30 * M_PI / 180) - z * (map->scale / 2);
	p.x = (int)iso_x + (WINDOW_WIDTH / 2);
	p.y = (int)iso_y + (WINDOW_HEIGHT / 2);
	return (p);
}

void	get_scale(t_map *map)
{
	float	scale_x;
	float	scale_y;

	scale_x = WINDOW_WIDTH / (float)map->width / 2;
	scale_y = WINDOW_HEIGHT / (float)map->height / 2;
	if (scale_x < scale_y)
		map->scale = scale_x;
	else
		map->scale = scale_y;
}

void	draw_line(t_map *map, t_point2d p1, t_point2d p2, int color)
{
	int dx = abs(p2.x - p1.x);
	int sx = (p1.x < p2.x) ? 1 : -1;
	int dy = -abs(p2.y - p1.y);
	int sy = (p1.y < p2.y) ? 1 : -1;
	int err = dx + dy;
	int e2;

	while (1)
	{
		my_mlx_pixel_put(map, p1.x, p1.y, COLOR);
		if (p1.x == p2.x && p1.y == p2.y)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			p1.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			p1.y += sy;
		}
	}
}

void	my_mlx_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

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