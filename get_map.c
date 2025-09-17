/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:44:56 by wschafer          #+#    #+#             */
/*   Updated: 2025/09/17 13:45:18 by wschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*get_map(char *file)
{
	t_map	*map;

	map = NULL;
	map = malloc(sizeof(t_map));
	if (!map)
		error(map, "Malloc failed for map struct");
	map->values = NULL;
	get_dimensions(map, file);
	allocate_array(map);
	fill_array(map, file);
	return (map);
}

void	get_dimensions(t_map *map, char *file)
{
	int		fd;
	int		tokens;
	char	*line;
	int		diff_arrow;

	map->height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(map, "Can't read the file");
	diff_arrow = 0;
	line = get_next_line(fd);
	while (line)
	{
		tokens = count_tokens_in_string(line, ' ');
		if (!check_tokens(map, tokens))
			diff_arrow++;
		free(line);
		map->height++;
		line = get_next_line(fd);
	}
	close(fd);
	if (map->height == 0 || map->width == 0)
		error(map, "Empty map");
	if (diff_arrow)
		error(map, "Different lengths of rows");
}

void	allocate_array(t_map *map)
{
	map->values = malloc(sizeof(int *) * map->height);
	if (!map->values)
		error(map, "Malloc failed for rows");
}

char	**get_clean_split(char *line, t_map *map)
{
	char	*trimmed;
	char	**split;

	trimmed = ft_strtrim(line, " \n");
	free(line);
	if (!trimmed)
		error(map, "Trim failed");
	split = ft_split(trimmed, ' ');
	free(trimmed);
	if (!split)
		error(map, "Split failed");
	if ((int)count_tokens(split) != map->width)
		error_split(map, split);
	return (split);
}

void	fill_array(t_map *map, char *file)
{
	int		fd;
	int		y;
	char	*line;
	char	**split;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(map, "Can't read the file");
	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		split = get_clean_split(line, map);
		map->values[y] = char_arr_to_int_arr(split, map->width);
		if (!map->values[y])
			error_split(map, split);
		free_split(split);
		y++;
	}
	close(fd);
}
