/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:54:04 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/11 17:08:04 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	frame_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	move_player(game);
	draw_background(game, game->data);
	draw_raycasting(game);
}
