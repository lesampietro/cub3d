/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:54:12 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/10 23:54:26 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_aim_circle(t_game *game)
{
	int		x;
	int		y;
	float	distance;

	y = WINDOW_HEIGHT / 2 - AIM_RADIUS - AIM_THICK;
	while (y <= WINDOW_HEIGHT / 2 + AIM_RADIUS + AIM_THICK)
	{
		x = WINDOW_WIDTH / 2 - AIM_RADIUS - AIM_THICK;
		while (x <= WINDOW_WIDTH / 2 + AIM_RADIUS + AIM_THICK)
		{
			distance = sqrtf((x - WINDOW_WIDTH / 2) * (x - WINDOW_WIDTH / 2) + \
				(y - WINDOW_HEIGHT / 2) * (y - WINDOW_HEIGHT / 2));
			if (distance >= AIM_RADIUS - AIM_THICK / 2 && \
				distance <= AIM_RADIUS + AIM_THICK / 2)
			{
				if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
					mlx_put_pixel(game->mlx_image, x, y, \
						convert_rgb(255, 255, 0));
			}
			x++;
		}
		y++;
	}
	mlx_put_pixel(game->mlx_image, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, \
		convert_rgb(255, 255, 0));
}

static void	draw_health_bar(t_game *game)
{
	int	x;
	int	y;

	y = 10;
	while (y < 10 + 23)
	{
		x = (WINDOW_WIDTH - 208) / 2;
		while (x < (WINDOW_WIDTH - 208) / 2 + 208)
		{
			if (x < (WINDOW_WIDTH - 208) / 2 + 4 || x >= (WINDOW_WIDTH - 208) \
				/ 2 + 204 || y < 10 + 4 || y >= 10 + 19)
			{
				mlx_put_pixel(game->mlx_image, x, y, \
					convert_rgb(255, 255, 255));
			}
			else if (x < (WINDOW_WIDTH - 208) / 2 + 4 + (int)(200 \
				* (game->player_health / 100.0)))
				mlx_put_pixel(game->mlx_image, x, y, convert_rgb(255, 0, 0));
			x++;
		}
		y++;
	}
}

void	ui_init(t_game *game)
{
	draw_aim_circle(game);
	draw_health_bar(game);
	if (game->total_items > 0)
		draw_progress_bar(game);
}
