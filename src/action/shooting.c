#include "../../includes/cub3d.h"

static int	shot_id(t_game *game)
{
	int		i;
	int		hit_index;
	float	min_dist;

	i = 0;
	hit_index = -1;
	min_dist = INFINITY;
	while (i < game->element_count)
	{
		check_target(game, i, &hit_index, &min_dist);
		i++;
	}
	return (hit_index);
}

void	hit_texture_timer(t_game *game, int i)
{
	uint64_t start;

	start = get_time_in_ms();
	while (get_time_in_ms() - start < 50)
		;
	game->element[i].got_hit = false;
	if (game->element[i].current_texture == game->element[i].hit_texture)
		game->element[i].current_texture = game->element[i].idle_texture;
}

void	shoot_hit(t_game *game)
{
	int	hit_index;

	hit_index = shot_id(game);
	if (hit_index >= 0 && game->element[hit_index].type == ENEMY)
	{
		game->element[hit_index].health -= PLAYER_DAMAGE;
		game->element[hit_index].got_hit = true;
		game->element[hit_index].current_texture = game->element[hit_index].hit_texture;
		// hit_texture_timer(game, hit_index);
		if (game->element[hit_index].health <= 0)
		{
			game->element[hit_index].alive = false;
			game->data->map[(int)game->element[hit_index].y][(int)game->element[hit_index].x] = '0';
		}

	}
}
