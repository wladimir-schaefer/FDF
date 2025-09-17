/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:44:24 by wschafer          #+#    #+#             */
/*   Updated: 2025/09/17 13:44:38 by wschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	*malloc_int_array(int width)
{
	int	*arr;

	arr = malloc(width * sizeof(int));
	if (!arr)
		return (NULL);
	return (arr);
}

int	fill_values(int *arr, char **split, int width)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (split[i])
	{
		if (split[i][0] != '\0')
		{
			if (j >= width)
				return (0);
			arr[j] = ft_atoi(split[i]);
			j++;
		}
		i++;
	}
	if (j != width)
		return (0);
	return (1);
}

int	*char_arr_to_int_arr(char **split, int width)
{
	int	*arr;

	arr = malloc_int_array(width);
	if (!arr)
		return (NULL);
	if (!fill_values(arr, split, width))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
