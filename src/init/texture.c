/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:54:31 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/11 15:33:00 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	load_wall_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i] = mlx_load_png(game->data->direction[i]);
		if (!game->texture[i])
		{
			printf(BPINK"Error loading texture: %s\n"RST,
				game->data->direction[i]);
			free_and_exit(game, 1);
		}
		i++;
	}
}

void	init_textures(t_game *game)
{
	load_wall_textures(game);
}
