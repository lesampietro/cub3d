#include "../../includes/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		game->player_dir = rotate_vector(game->player_dir, -1.5);
		game->camera_plane = rotate_vector(game->camera_plane, -1.5);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		game->player_dir = rotate_vector(game->player_dir, 1.5);
		game->camera_plane = rotate_vector(game->camera_plane, 1.5);
	}
}