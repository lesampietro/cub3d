#include "../../includes/cub3d.h"

static int shot_id(t_game *game)
{
    int   hit_index = -1;
    float min_dist   = INFINITY;
    int   shot_x     = WINDOW_WIDTH / 2;

    for (int i = 0; i < game->element_count; i++)
    {
        t_element *e = &game->element[i];
        if (!e->alive)
            continue;

        // 1) posição relativa
        float rel_x = e->x + 0.5f - game->player_pos.x;
        float rel_y = e->y + 0.5f - game->player_pos.y;

        // 2) projeção no plano da câmera
        float inv_det = 1.0f / (game->camera_plane.x * game->player_dir.y
                              - game->player_dir.x * game->camera_plane.y);
        float tr_x = inv_det * ( game->player_dir.y * rel_x
                               - game->player_dir.x * rel_y);
        float tr_y = inv_det * (-game->camera_plane.y * rel_x
                               + game->camera_plane.x * rel_y);

        if (tr_y <= 0.0f)  // atrás da câmera
            continue;

        // 3) largura do sprite em pixels
        int sprite_w = abs((int)(WINDOW_HEIGHT / tr_y));

        // 4) limites horizontais na tela
        int sprite_screen_x = (int)((WINDOW_WIDTH / 2) * (1 + tr_x / tr_y));
        int start_x = sprite_screen_x - sprite_w / 2;
        int end_x   = sprite_screen_x + sprite_w / 2;

        if (shot_x < start_x || shot_x > end_x)
            continue;

        // 5) profundidade contra paredes
        if (tr_y < game->raycasting->z_buffer[shot_x])
        {
            if (tr_y < min_dist)
            {
                min_dist  = tr_y;
                hit_index = i;
            }
        }
    }
    return hit_index;
}


void shoot_hit(t_game *game)
{
	int hit_index;

	hit_index = shot_id(game);
	if (hit_index >= 0 && game->element->type == ENEMY)
	{
		game->element[hit_index].health -= 10;
		printf("Hit! Element %d health: %d\n", hit_index, game->element[hit_index].health);
		if (game->element[hit_index].health <= 0)
			game->element[hit_index].alive = false;
	}
}
