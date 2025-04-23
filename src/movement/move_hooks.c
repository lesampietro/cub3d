#include "../../includes/cub3d.h"

void try_move(t_game *game, t_vector dir, float speed)
{
	float new_x = game->player_pos.x + dir.x * speed;
	float new_y = game->player_pos.y + dir.y * speed;

	if (game->data->map[(int)(game->player_pos.y)][(int)new_x] != '1')
		game->player_pos.x += dir.x * speed;
	if (game->data->map[(int)new_y][(int)(game->player_pos.x)] != '1')
		game->player_pos.y += dir.y * speed;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
		exit(0);
	}
	if (keydata.key == MLX_KEY_LEFT)
	{
		game->player_dir = rotate_vector(game->player_dir, -3);
		game->camera_plane = rotate_vector(game->camera_plane, -3);
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		game->player_dir = rotate_vector(game->player_dir, 3);
		game->camera_plane = rotate_vector(game->camera_plane, 3);
	}
	if (keydata.key == MLX_KEY_W)
		try_move(game, game->player_dir, 0.12);
	if (keydata.key == MLX_KEY_S)
		try_move(game, game->player_dir, -0.12);
	if (keydata.key == MLX_KEY_D)
		try_move(game, game->camera_plane, 0.12);
	if (keydata.key == MLX_KEY_A)
		try_move(game, game->camera_plane, -0.12);
}