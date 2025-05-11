/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:21 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/10 23:53:22 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	mouse_rotation(t_game *game)
{
	int		x;
	int		y;
	int		delta_x;
	float	angle;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	delta_x = x - game->mouse_prev_x;
	if (delta_x != 0)
	{
		angle = delta_x * SENSITIVITY;
		game->player_dir = rotate_vector(game->player_dir, angle);
		game->camera_plane = rotate_vector(game->camera_plane, angle);
	}
	mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	game->mouse_prev_x = WINDOW_WIDTH / 2;
}

void	mouse_hook(mouse_key_t button, action_t action,
	modifier_key_t mods, void *param)
{
	t_game	*game;

	(void)mods;
	game = (t_game *)param;
	if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_PRESS)
	{
		shoot_hit(game);
		game->keys.mouse_left = true;
	}
	else if (button == MLX_MOUSE_BUTTON_LEFT && action == MLX_RELEASE)
		game->keys.mouse_left = false;
}
