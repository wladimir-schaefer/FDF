/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:07:35 by wschafer          #+#    #+#             */
/*   Updated: 2025/09/11 15:38:47 by wschafer         ###   ########.fr       */
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
	draw(map);
	


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