#include "../../includes/cub3d.h"

void frame_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	move_player(game);
	draw_background(game, game->data);
	draw_raycasting(game);
	draw_minimap(game);
}