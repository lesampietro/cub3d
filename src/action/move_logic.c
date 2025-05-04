#include "../../includes/cub3d.h"

void	try_move(t_game *game, t_vector dir, float speed)
{
	float	new_x;
	float	new_y;

	new_x = game->player_pos.x + dir.x * speed;
	new_y = game->player_pos.y + dir.y * speed;
	if (game->data->map[(int)(game->player_pos.y)][(int)new_x] != '1')
		game->player_pos.x += dir.x * speed;
	if (game->data->map[(int)new_y][(int)(game->player_pos.x)] != '1')
		game->player_pos.y += dir.y * speed;
}

void	handle_movement(t_game *game, float speed)
{
	if (game->keys.w)
		try_move(game, game->player_dir, speed);
	if (game->keys.s)
		try_move(game, game->player_dir, -speed);
	if (game->keys.a)
		try_move(game, game->camera_plane, -speed);
	if (game->keys.d)
		try_move(game, game->camera_plane, speed);
}

void	move_player(t_game *game)
{
	if (game->keys.shift)
		handle_movement(game, MOVE_SPEED * SPRINT_MULTIPLIER);
	else
		handle_movement(game, MOVE_SPEED);
	if (game->keys.left)
	{
		game->player_dir = rotate_vector(game->player_dir, -ROTATE_SPEED);
		game->camera_plane = rotate_vector(game->camera_plane, -ROTATE_SPEED);
	}
	if (game->keys.right)
	{
		game->player_dir = rotate_vector(game->player_dir, ROTATE_SPEED);
		game->camera_plane = rotate_vector(game->camera_plane, ROTATE_SPEED);
	}
}
