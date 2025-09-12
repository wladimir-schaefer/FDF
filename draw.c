#include "fdf.h"

void	draw(t_map *map)
{
	map->mlx = mlx_init();
	map->mlx_win = mlx_new_window(map->mlx, 1920, 1080, "FDF");
	map->img = mlx_new_image(map->mlx, 1920, 1080);
	map->addr = mlx_get_data_addr(map->img, &map->bits_per_pixel, &map->line_length,
								&map->endian);
	my_mlx_pixel_put(map, 100, 100, 0x00FF0000);
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img, 0, 0);
	mlx_key_hook(map->mlx_win, key_handler, map);
	mlx_hook(map->mlx_win, 17, 0, close_handler, map);
	mlx_loop(map->mlx);
}

void	*get_three_dim_point(t_map *map)
{
	t_point2d	p1;
	t_point2d	p2;
	t_point2d	p3;
	int			x;
	int			y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			p1 = project_point(x, y, map->values[y][x]);
			if (x < map->width - 1)
			{
				p2 = project_point(x + 1, y, map->values[y][x + 1]);
				draw_line(map, p1, p2);
			}
			if (y < map->height - 1)
			{
				p3 = project_point(y + 1, y, map->values[y + 1][x]);
				draw_line(map, p1, p2);
			}
			x++;
		}
		y++;
	}
}

t_point2d	project_point(int x, int y, int z)
{
	t_point2d	p;
	float		iso_x;
	float		iso_y;

	iso_x = (x - y) * cos(30 * M_PI / 180);
	iso_y = (x + y) * sin(30 * M_PI / 180) - z;
	p.x = (int)iso_x;
	p.y = (int)iso_y;
	return (p);
}

draw_line(map, p1, p2);