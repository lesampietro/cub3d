/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:54:04 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 00:03:52 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void fill_with_black(t_game *game)
{
	int x;
	int y;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		y = 0;
		while (y < WINDOW_HEIGHT)
		{
			mlx_put_pixel(game->mlx_image, x, y, 0x000000FF);
			y++;
		}
		x++;
	}
}
