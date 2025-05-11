/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:58:27 by lsampiet          #+#    #+#             */
/*   Updated: 2025/05/11 15:29:33 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	process_info(t_data *data)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			c = data->map[y][x];
			if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
			{
				data->pov = c;
				data->game->player_pos.x = x + 0.5f;
				data->game->player_pos.y = y + 0.5f;
				data->map[y][x] = '0';
			}
			x++;
		}
		y++;
	}
}
