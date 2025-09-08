#include "fdf.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_map	*map = NULL;
	void	*img;
	void	*mlx;

	if (argc != 2)
		error(map, "Wrong number of arguments");
	map = get_map(argv[1]);
	
	mlx = mlx_init();
	img = mlx_new_image(mlx, 1920, 1080);
	mlx_loop(mlx);

	// Test print
	// for (int y = 0; y < map->height; y++)
	// {
	// 	for (int x = 0; x < map->width; x++)
	// 		printf("%3d ", map->values[y][x]);
	// 	printf("\n");
	// }

	free_map(map);
	return (0);




	// exit(0);
}

void	error(t_map *map, char *error_message)
{
	ft_printf("%s\n", error_message);
	free_map(map);
	exit (1);
}