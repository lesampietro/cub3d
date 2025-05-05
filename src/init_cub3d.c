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

// void read_map(t_game *game)

void init_default_values(t_game *game)
{
	game->player_health = 100;
	// game->element_count = 0;
}

void init_window(t_game *game)
{
	// int32_t moni_w;
	// int32_t moni_h;

	// moni_w = 0;
	// moni_h = 0;
	init_default_values(game);
	define_initial_plane(game);
	
	// AQUI

	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	// if (!game->mlx)
	// 	ft_error(ERROR_MLX_LOAD, NULL);
	game->mlx_image = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// if (!game->mlx_image)
	// 	ft_error(ERROR_MLX_LOAD, NULL);
	mlx_image_to_window(game->mlx, game->mlx_image, 0, 0);
	// mlx_get_monitor_size(0, &moni_w, &moni_h);
	// mlx_set_window_limit(game->mlx, TILE, TILE, moni_w, moni_h);
	// if (game->mlx->width > moni_w || game->mlx->height > moni_h)
	// {
	// 	ft_error(ERROR_MAP_2BIG, NULL);
	// 	free_game(game);
	// }
}

int32_t init_game(char *argv, t_game *game)
{
	(void)argv;
	// game->map = read_map(argv);
	// count_map_size(game);
	init_window(game);
	// init_game_image(game);
	// get_player_pos(game->map, &game->player_pos);
	// occurence_count(game->map, &game->occ);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
	// Depois de criar `game->mlx` e abrir a janela:
	mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	// “Semeia” o último x do mouse como o centro
	game->mouse_prev_x = WINDOW_WIDTH/2;

	mlx_key_hook(game->mlx, key_hook, game);
	mlx_mouse_hook(game->mlx, mouse_hook, game);
	mlx_loop_hook(game->mlx, frame_loop, game);
	mlx_loop(game->mlx);
	// mlx_close_hook(game->mlx, 0, game);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	// free_game(game);
	return (EXIT_SUCCESS);
}