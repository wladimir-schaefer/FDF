/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:07:35 by wschafer          #+#    #+#             */
/*   Updated: 2025/09/17 13:46:44 by wschafer         ###   ########.fr       */
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
	exit (1);
}

void	error_split(t_map *map, char **split)
{
	free_split(split);
	error(map, "Malloc failed for row");
}
