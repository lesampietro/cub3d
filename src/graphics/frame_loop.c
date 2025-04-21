#include "../../includes/cub3d.h"

void frame_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw_background(game);
	draw_raycasting(game);
}