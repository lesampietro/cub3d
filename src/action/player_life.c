#include "../../includes/cub3d.h"

void	check_player_life(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->player_health > 0)
		return ;
	game->player_health = 0;
	mlx_close_window(game->mlx);
	mlx_terminate(game->mlx);
	printf("Game Over! You are dead.\n");
}
