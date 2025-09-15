#include "fdf.h"

void	draw_line(t_map *map, t_point2d p1, t_point2d p2, int color)
{
	t_line line;

	line = init_line(p1, p2);
	while (1)
	{
		my_mlx_pixel_put(map, p1.x, p1.y, color);
		if (p1.x == p2.x && p1.y == p2.y)
			break ;
		line.e2 = 2 * line.err;
		if (line.e2 >= line.dy)
		{
			line.err += line.dy;
			p1.x += line.sx;
		}
		if (line.e2 <= line.dx)
		{
			line.err += line.dx;
			p1.y += line.sy;
		}
	}
}

t_line	init_line(t_point2d p1, t_point2d p2)
{
	t_line line;

	line.dx = abs(p2.x - p1.x);
	if (p1.x < p2.x)
		line.sx = 1;
	else
		line.sx = -1;
	line.dy = -abs(p2.y - p1.y);
	if (p1.y < p2.y)
		line.sy = 1;
	else
		line.sy = -1;
	line.err = line.dx + line.dy;
	return (line);
}