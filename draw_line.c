#include "fdf.h"

void	draw_line(t_map *map, t_point2d p1, t_point2d p2, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;

	dx = abs(p2.x - p1.x);
	dy = -abs(p2.y - p1.y);
	sx = get_step(p1.x, p2.x);
	sy = get_step(p1.y, p2.y);
	err = dx + dy;
	while (1)
	{
		my_mlx_pixel_put(map, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		update_err_and_step(&err, dx, dy, &p1, sx, sy);
	}
}

void	update_err_and_step(int *err, int dx, int dy, t_point2d *p, int sx, int sy)
{
	int e2;

	e2 = 2 * (*err);
	if (e2 >= dy)
	{
		*err += dy;
		p->x += sx;
	}
	if (e2 <= dx)
	{
		*err += dx;
		p->y += sy;
	}
}

int	get_step(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}
