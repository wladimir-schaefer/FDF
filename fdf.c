/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:07:35 by wschafer          #+#    #+#             */
/*   Updated: 2025/09/10 19:07:15 by wschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_map	*map;

	map = NULL;
	if (argc != 2)
		error(map, "Wrong number of arguments");
	map = get_map(argv[1]);
	
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

	free_map(map);
	return (0);

	// exit(0);
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

void	error(t_map *map, char *error_message)
{
	ft_printf("%s\n", error_message);
	if (map)
		free_map(map);
	exit (1);
}
void	error_str(char *str, char *error_message)
{
	ft_printf("%s\n", error_message);
	if (str)
		free(str);
	// exit (1);
}
void	error_split(t_map *map, char **split)
{
	free_split(split);
	error(map, "Malloc failed for row");
}











	// Test print
	// for (int y = 0; y < map->height; y++)
	// {
	// 	for (int x = 0; x < map->width; x++)
	// 		printf("%3d ", map->values[y][x]);
	// 	printf("\n");
	// }