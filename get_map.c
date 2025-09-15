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
		split = ft_split(line, ' ');
		if (!split)
			error(map, "Split failed");
		map->values[y] = char_arr_to_int_arr(split, map->width);
		if (!map->values[y])
			error_split(map, split);
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
