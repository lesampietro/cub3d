#include "../../includes/cub3d.h"

void frame_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mouse_rotation(game);
	move_player(game);
	draw_background(game, game->data);
	draw_raycasting(game);
	render_enemy(game, game->enemy);
	draw_minimap(game);
}