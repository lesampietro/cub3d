#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
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
	data->f = NULL;
}

void	free_element_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].idle_texture_path)
			mlx_delete_texture(game->element[i].idle_texture);
		if (game->element[i].shooting_texture_path)
			mlx_delete_texture(game->element[i].shooting_texture);
		if (game->element[i].hit_texture_path)
			mlx_delete_texture(game->element[i].hit_texture);
		i++;
	}
}

void	free_mlx(t_game *game)
{
	if (game->mlx_image)
		mlx_delete_image(game->mlx, game->mlx_image);
	if (game->weapon_texture)
		mlx_delete_texture(game->weapon_texture);
	if (game->weapon_shooting_texture)
		mlx_delete_texture(game->weapon_shooting_texture);
	if (game->texture[0])
		mlx_delete_texture(game->texture[0]);
	if (game->texture[1])
		mlx_delete_texture(game->texture[1]);
	if (game->texture[2])
		mlx_delete_texture(game->texture[2]);
	if (game->texture[3])
		mlx_delete_texture(game->texture[3]);
	if (game->texture_buf)
		mlx_delete_texture(game->texture_buf);
	if (game->data->direction[0])
		free(game->data->direction[0]);
	if (game->data->direction[1])
		free(game->data->direction[1]);
	if (game->data->direction[2])
		free(game->data->direction[2]);
	if (game->data->direction[3])
		free(game->data->direction[3]);
	
	free_element_textures(game);
	
}

void	free_and_exit(t_game *game)
{
	free_map(game->data->map);
	free_color_array(game->data);
	free_mlx(game);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	exit(EXIT_SUCCESS);
}