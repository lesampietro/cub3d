#include "../../includes/cub3d.h"

static bool	is_alive_and_in_front(t_game *g, int i, float *tr_x, float *tr_y)
{
	t_element	*e;
	float		inv_det;
	float		rel_x;
	float		rel_y;

	e = &g->element[i];
	if (!e->alive)
		return (false);
	rel_x = e->x - g->player_pos.x;
	rel_y = e->y - g->player_pos.y;
	inv_det = 1.0f / (g->camera_plane.x * g->player_dir.y
			- g->player_dir.x * g->camera_plane.y);
	*tr_x = inv_det * (g->player_dir.y * rel_x
			- g->player_dir.x * rel_y);
	*tr_y = inv_det * (-g->camera_plane.y * rel_x
			+ g->camera_plane.x * rel_y);
	if (*tr_y <= 0.0f)
		return (false);
	return (true);
}

static bool	is_within_beam(float tr_x, float tr_y)
{
	int	sprite_x;
	int	dx;
	int	margin;

	sprite_x = (int)((WINDOW_WIDTH / 2) * (1 + tr_x / tr_y));
	dx = sprite_x - (WINDOW_WIDTH / 2);
	margin = (int)((WINDOW_HEIGHT / tr_y) * 0.8f) / 2;
	if (abs(dx) > margin)
		return (false);
	return (true);
}

static bool	is_not_blocked_by_wall(t_game *g, float tr_y, int i)
{
	if (g->element[i].type != ENEMY)
		return (true);
	if (tr_y - 0.5f < g->raycasting->z_buffer[WINDOW_WIDTH / 2])
		return (true);
	return (false);
}

static void	update_hit_if_closer(int *hit_index, float *min_dist,
	float tr_y, int i)
{
	if (tr_y < *min_dist)
	{
		*min_dist = tr_y;
		*hit_index = i;
	}
}

bool	check_target(t_game *g, int i, int *hit_index, float *min_dist)
{
	float	tr_x;
	float	tr_y;

	if (!is_alive_and_in_front(g, i, &tr_x, &tr_y))
		return (false);
	if (!is_within_beam(tr_x, tr_y))
		return (false);
	if (!is_not_blocked_by_wall(g, tr_y, i))
		return (false);
	update_hit_if_closer(hit_index, min_dist, tr_y, i);
	return (true);
}

