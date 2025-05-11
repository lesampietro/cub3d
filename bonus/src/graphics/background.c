/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:51 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/10 23:53:52 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_background(t_game *game, t_data *data)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < game->mlx_image->height / 2)
	{
		x = 0;
		while (x < game->mlx_image->width)
		{
			mlx_put_pixel(game->mlx_image, x, y, data->ceiling);
			x++;
		}
		y++;
	}
	while (y < game->mlx_image->height)
	{
		x = 0;
		while (x < game->mlx_image->width)
		{
			mlx_put_pixel(game->mlx_image, x, y, data->floor);
			x++;
		}
		y++;
	}
}
