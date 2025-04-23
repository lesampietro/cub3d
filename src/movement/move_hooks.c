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

void move_player(t_game *game)
{
	if (game->keys->w)
		try_move(game, game->player_dir, MOVE_SPEED);
	if (game->keys->s)
		try_move(game, game->player_dir, -MOVE_SPEED);
	if (game->keys->a)
		try_move(game, game->camera_plane, -MOVE_SPEED);
	if (game->keys->d)
		try_move(game, game->camera_plane, MOVE_SPEED);
	if (game->keys->left)
	{
		game->player_dir = rotate_vector(game->player_dir, -ROTATE_SPEED);
		game->camera_plane = rotate_vector(game->camera_plane, -ROTATE_SPEED);
	}
	if (game->keys->right)
	{
		game->player_dir = rotate_vector(game->player_dir, ROTATE_SPEED);
		game->camera_plane = rotate_vector(game->camera_plane, ROTATE_SPEED);
	}
}

static void pressed(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_LEFT)
		game->keys->left = true;
	if (keydata.key == MLX_KEY_RIGHT)
		game->keys->right = true;
	if (keydata.key == MLX_KEY_W)
		game->keys->w = true;
	if (keydata.key == MLX_KEY_S)
		game->keys->s = true;
	if (keydata.key == MLX_KEY_D)
		game->keys->d = true;
	if (keydata.key == MLX_KEY_A)
		game->keys->a = true;
}

static void released(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_LEFT)
		game->keys->left = false;
	if (keydata.key == MLX_KEY_RIGHT)
		game->keys->right = false;
	if (keydata.key == MLX_KEY_W)
		game->keys->w = false;
	if (keydata.key == MLX_KEY_S)
		game->keys->s = false;
	if (keydata.key == MLX_KEY_D)
		game->keys->d = false;
	if (keydata.key == MLX_KEY_A)
		game->keys->a = false;
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
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
		pressed(keydata, game);
	else if (keydata.action == MLX_RELEASE)
		released(keydata, game);
}