/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:55:21 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/12 20:32:27 by fcaldas-         ###   ########.fr       */
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
}

void	init_window(t_game *game)
{
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
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop_hook(game->mlx, frame_loop, game);
	mlx_loop(game->mlx);
	free_and_exit(game, 0);
	return (EXIT_SUCCESS);
}
