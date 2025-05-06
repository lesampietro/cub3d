#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_color_array(t_data *data)
{
	if (data->f)
		free(data->f);
	if (data->c)
		free(data->c);
	data->c = NULL;
}

void	free_and_exit(t_game *game)
{
	int	i;

	i = 0;
	free_map(game->data->map);
	free_color_array(game->data);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	exit(EXIT_SUCCESS);
}