#include "../../includes/cub3d.h"

// void	mouse_hook(t_game *game)
// {
// 	int		*x_prev;
// 	int		x;
// 	int		y;

// 	x_prev = &game->mouse_pos_start.x;
// 	mlx_get_mouse_pos(game->mlx, &x, &y);
// 	if (x - *x_prev > 0)
// 	{
// 		game->player_dir = rotate_vector(game->player_dir, 0.1);
// 		game->camera_plane = rotate_vector(game->camera_plane, 0.1);
// 	}
// 	else if (x - *x_prev < 0)
// 	{
// 		game->player_dir = rotate_vector(game->player_dir, -0.1);
// 		game->camera_plane = rotate_vector(game->camera_plane, -0.1);
// 	}
// }

void mouse_rotation(t_game *game)
{
	int x, y;
	int delta_x;

	mlx_get_mouse_pos(game->mlx, &x, &y);
	delta_x = x - game->mouse_prev_x;

	if (delta_x != 0)
	{
		float angle = delta_x * SENSITIVITY;
		game->player_dir = rotate_vector(game->player_dir, angle);
		game->camera_plane = rotate_vector(game->camera_plane, angle);
	}

	game->mouse_prev_x = x;

	// (Opcional) Resetar para o centro da tela após ler o movimento:
	mlx_set_mouse_pos(game->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	game->mouse_prev_x = WINDOW_WIDTH / 2;
}
