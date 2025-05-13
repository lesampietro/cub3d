/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:07 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/13 00:09:48 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	enemy_texture_reset(t_game *game)
{
	uint64_t	now;
	int			i;

	i = 0;
	now = get_time_in_ms();
	while (i < game->element_count)
	{
		if (now - game->element[i].last_hit_time > 100)
		{
			game->element[i].got_hit = false;
			if (game->element[i].current_texture
				== game->element[i].hit_texture)
				game->element[i].current_texture
					= game->element[i].idle_texture;
		}
		i++;
	}
}
