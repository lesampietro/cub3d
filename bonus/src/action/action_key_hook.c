/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_key_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:02 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/13 15:14:22 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	pressed(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_LEFT)
		game->keys.left = true;
	if (keydata.key == MLX_KEY_RIGHT)
		game->keys.right = true;
	if (keydata.key == MLX_KEY_W)
		game->keys.w = true;
	if (keydata.key == MLX_KEY_S)
		game->keys.s = true;
	if (keydata.key == MLX_KEY_D)
		game->keys.d = true;
	if (keydata.key == MLX_KEY_A)
		game->keys.a = true;
	if (keydata.key == MLX_KEY_LEFT_SHIFT)
		game->keys.shift = true;
}

static void	released(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_LEFT)
		game->keys.left = false;
	if (keydata.key == MLX_KEY_RIGHT)
		game->keys.right = false;
	if (keydata.key == MLX_KEY_W)
		game->keys.w = false;
	if (keydata.key == MLX_KEY_S)
		game->keys.s = false;
	if (keydata.key == MLX_KEY_D)
		game->keys.d = false;
	if (keydata.key == MLX_KEY_A)
		game->keys.a = false;
	if (keydata.key == MLX_KEY_LEFT_SHIFT)
		game->keys.shift = false;
}

void	minimap_hook(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		game->minimap = !game->minimap;
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_PRESS)
		game->minimap_enemies = !game->minimap_enemies;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	minimap_hook(keydata, game);
	if (keydata.key == MLX_KEY_ESCAPE)
		free_and_exit(game, EXIT_SUCCESS);
	if (mlx_is_mouse_down(game->mlx, MLX_MOUSE_BUTTON_LEFT))
		game->keys.mouse_left = true;
	else
		game->keys.mouse_left = false;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		pressed(keydata, game);
	else if (keydata.action == MLX_RELEASE)
		released(keydata, game);
}
