#include "../includes/cub3d.h"

// void init_game_image(t_game *game)
// {
// 	display_img(game);
// 	put_floor_n_walls(game);
// 	put_collects_n_exit(game);
// 	game->img.exit->enabled = false;
// 	put_player(game);
// 	display_icon(game);
// }

void init_window(t_game *game)
{
	// int32_t moni_w;
	// int32_t moni_h;

	// moni_w = 0;
	// moni_h = 0;
	init_textures(game);
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
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_mouse_hook(game->mlx, mouse_hook, game);
	mlx_loop_hook(game->mlx, frame_loop, game);
	// mlx_close_hook(game->mlx, 0, game);
	mlx_loop(game->mlx);
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	// free_game(game);
	return (EXIT_SUCCESS);
}