/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_key_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:02 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 00:59:53 by nasser           ###   ########.fr       */
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
	// if (keydata.key == MLX_KEY_ENTER)
	// 	game->keys.enter = true;
		
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
	// if (keydata.key == MLX_KEY_ENTER)
	// 	game->keys.enter = false;
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
	if (keydata.key == MLX_KEY_ENTER && keydata.action == MLX_PRESS)
	{
		if (game->menu_active)
		{
			if (game->phrase_image)
				mlx_delete_image(game->mlx, game->phrase_image);
			if (game->continue_phrase_image)
				mlx_delete_image(game->mlx, game->continue_phrase_image);
			game->menu_active = false;
			game->game_won = false;
			game->game_lost = false;
		}
		else if (game->game_won || game->game_lost)
		{
		if (game->phrase_image)
			mlx_delete_image(game->mlx, game->phrase_image);
		game->phrase_image = mlx_put_string(game->mlx, "WELCOME TO CUB3D", WINDOW_WIDTH / 2 - 60, WINDOW_HEIGHT / 2 - 10);
		if (game->continue_phrase_image)
			mlx_delete_image(game->mlx, game->continue_phrase_image);
		game->continue_phrase_image = mlx_put_string(game->mlx, "Press ENTER to START", WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT - WINDOW_HEIGHT / 10);
		game->menu_active = true;
		game->game_won = false;
		game->game_lost = false;
		reset_game(game);
		game->menu_active = true;
		}
	}
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
