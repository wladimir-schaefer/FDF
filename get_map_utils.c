#include "fdf.h"

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
	while (*s != '\0' && *s != '\n')
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

int	check_tokens(t_map *map, int tokens)
{
	if (map->height == 0)
	{
		map->width = tokens;
		return (1);
	}
	else if (tokens != map->width)
		return (0);
	return (1);
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
	int	y;

	if (!map)
		return ;
	if (map->values)
	{
		y = 0;
		while (y < map->height)
		{
			free(map->values[y]);
			// ft_printf("Freed row %d\n", y);
			y++;
		}
		free(map->values);
		// ft_printf("Freed values array\n");
	}
	free(map);
	// ft_printf("Freed map struct\n");
}
