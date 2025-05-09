#include "../../includes/cub3d.h"

void	frame_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	check_player_life(game);
	enemy_texture_reset(game);
	if (game->total_items > 0)
		objective_check(game);
	move_player(game);
	enemy_shots(game);
	draw_background(game, game->data);
	draw_raycasting(game);
	render_elements(game);
	draw_minimap(game);
	draw_weapon(game);
	mouse_rotation(game);
	ui_init(game);
}
