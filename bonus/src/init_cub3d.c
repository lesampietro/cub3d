/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:55:21 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 00:59:06 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	define_initial_plane(t_game *game)
{
	if (game->data->pov == 'N')
	{
		game->player_dir = create_vector(0, -1);
		game->camera_plane = create_vector(0.66, 0);
	}
	else if (game->data->pov == 'S')
	{
		game->player_dir = create_vector(0, 1);
		game->camera_plane = create_vector(-0.66, 0);
	}
	else if (game->data->pov == 'W')
	{
		game->player_dir = create_vector(-1, 0);
		game->camera_plane = create_vector(0, -0.66);
	}
	else if (game->data->pov == 'E')
	{
		game->player_dir = create_vector(1, 0);
		game->camera_plane = create_vector(0, 0.66);
	}
	game->player_initial_dir = game->player_dir;
	game->player_initial_plane = game->camera_plane;
}

void	init_default_values(t_game *game)
{
	game->minimap = false;
	game->minimap_enemies = false;
	game->player_health = 100;
}

void	init_window(t_game *game)
{
	init_default_values(game);
	define_initial_plane(game);
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	game->mlx_image = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_image_to_window(game->mlx, game->mlx_image, 0, 0);
}

int32_t	init_game(char *argv, t_game *game)
{
	(void)argv;
	init_window(game);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	game->mouse_prev_x = WINDOW_WIDTH / 2;	
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_mouse_hook(game->mlx, mouse_hook, game);
	mlx_loop_hook(game->mlx, frame_loop, game);
	mlx_loop(game->mlx);
	free_and_exit(game, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
