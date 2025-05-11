/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:55:48 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/11 16:32:45 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
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

void	free_texture_paths(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].idle_texture)
			mlx_delete_texture(game->element[i].idle_texture);
		if (game->element[i].shooting_texture)
			mlx_delete_texture(game->element[i].shooting_texture);
		if (game->element[i].hit_texture)
			mlx_delete_texture(game->element[i].hit_texture);
		i++;
	}
	if (game->data->direction[0])
		free(game->data->direction[0]);
	if (game->data->direction[1])
		free(game->data->direction[1]);
	if (game->data->direction[2])
		free(game->data->direction[2]);
	if (game->data->direction[3])
		free(game->data->direction[3]);
}

void	free_and_exit(t_game *game, int code)
{
	get_next_line(-2);
	free_map(game->data->map);
	free_color_array(game->data);
	free_texture_paths(game);
	if (game->data->fd)
		close(game->data->fd);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	if (code == 1)
		exit(EXIT_FAILURE);
	if (code == 0)
		exit(EXIT_SUCCESS);
}
