#include "fdf.h"
#include <stdio.h>

t_map	*get_map(char *file)
{
	t_map	*map = NULL;

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

	map->height = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(map, "Can't read the file");
	while ((line = get_next_line(fd)))
	{
		tokens = count_tokens_in_string(line, ' ');
		// printf("Line %d: tokens=%d\n", map->height + 1, tokens);
		if (map->height == 0)
			map->width = tokens;
		else if (tokens != map->width)
			error(map, "Different lengths of rows");
		free(line);
		map->height++;
	}
	close(fd);
}

void	allocate_array(t_map *map)
{
	map->values = malloc(sizeof(int *) * map->height);
	if (!map->values)
		error(map, "Malloc failed for rows");
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
	while ((line = get_next_line(fd)))
	{
		split = ft_split(line, ' ');
		if (!split)
			error(map, "Split failed");
		map->values[y] = char_arr_to_int_arr(split, map->width);
		if (!map->values[y])
		{
			free_split(split);
			error(map, "Malloc failed for row");
		}
		free(line);
		free_split(split);
		y++;
	}
	close(fd);
}

int	*char_arr_to_int_arr(char **split, int width)
{
	int	i;
	int	j;
	int	*arr;

	arr = malloc(width * sizeof(int));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (split[i])
	{
		if (split[i][0] != '\0')
		{
			arr[j] = ft_atoi(split[i]);
			j++;
		}
		i++;
	}
	return (arr);
}

size_t	count_tokens(char **split)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (split[i])
	{
		if (split[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

size_t	count_tokens_in_string(char const *s, char c)
{
	size_t	count;
	size_t	in_word;

	in_word = 0;
	count = 0;
	while (ft_isprint(*s))
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	free_map(t_map *map)
{
	int y;

	if (!map)
		return;
	if (map->values)
	{
		y = 0;
		while (y < map->height)
		{
			free(map->values[y]);
			y++;
		}
		free(map->values);
	}
	free(map);
}

// void	get_dimensions(t_map *map, char *file)
// {
// 	int		fd;
// 	int		tokens;
// 	char	*line;
// 	char	**split;

// 	map->height = 0;
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 		error(map, "Can't read the file");
// 	while ((line = get_next_line(fd)))
// 	{
// 		line = ft_strtrim(line, " \n");
// 		split = ft_split(line, ' ');
// 		if (!split)
// 			error(map, "Split failed");
// 		tokens = count_tokens(split);
// 		printf("Line %d: tokens=%d\n", map->height + 1, tokens);
// 		if (map->height == 0)
// 			map->width = tokens;
// 		else if (tokens != map->width)
// 			error(map, "Different lengths of rows");
// 		free_split(split);
// 		free(line);
// 		map->height++;
// 	}
// 	close(fd);
// }