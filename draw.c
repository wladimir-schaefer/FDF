/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:47:20 by wschafer          #+#    #+#             */
/*   Updated: 2025/09/17 13:52:52 by wschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw(t_map *map)
{
	map->mlx = mlx_init();
	map->mlx_win = mlx_new_window(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	map->img = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	map->addr = mlx_get_data_addr(map->img, &map->bits_per_pixel,
			&map->line_length, &map->endian);
	mlx_loop_hook(map->mlx, draw_map, map);
	mlx_key_hook(map->mlx_win, key_handler, map);
	mlx_hook(map->mlx_win, 17, 0, close_handler, map);
	mlx_loop(map->mlx);
}

int	draw_map(t_map *map)
{
	int	x;
	int	y;

	get_scale(map);
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
	mlx_put_image_to_window(map->mlx, map->mlx_win, map->img, 0, 0);
	return (0);
}

void	handle_point(t_map *map, int x, int y)
{
	t_point2d	p1;
	t_point2d	p2;

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

	iso_x = (x * map->scale - y * map->scale) * cos(30 * M_PI / 180);
	iso_y = (x * map->scale + y * map->scale) * sin(30 * M_PI / 180) 
		- z * (map->scale / 2);
	p.x = (int)iso_x + (WINDOW_WIDTH / 2);
	p.y = (int)iso_y + (WINDOW_HEIGHT / 3.5);
	return (p);
}
