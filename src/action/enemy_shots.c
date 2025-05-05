#include "../../includes/cub3d.h"

# include <sys/time.h>

uint64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	enemy_shoot_at_player(t_game *game, t_element *enemy)
{
	if (enemy->visible)
	{
		enemy->texture = enemy->shooting_texture;
		game->player_health -= 5;
	}
}

void	update_enemy_shooting(t_game *game, t_element *enemy)
{
	uint64_t now;

	now = get_time_in_ms();
	if (!enemy->alive)
		return ;
	if (!enemy->visible)
		enemy->first_visible_time = 0;
	if (enemy->first_visible_time == 0)
	{
		enemy->first_visible_time = now;
		return ;
	}
	if (now - enemy->first_visible_time < ENEMY_SHOOT_INTERVAL)
		return ;
	if (now - enemy->last_shot_time >= ENEMY_SHOOT_INTERVAL)
	{
		enemy_shoot_at_player(game, enemy);
		enemy->last_shot_time = now;
	}
}

void	enemy_shots(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].alive && game->element[i].type == ENEMY)
		{
			if (!game->element[i].visible)
				game->element[i].texture = game->element[i].idle_texture;
			update_enemy_shooting(game, &game->element[i]);
		}
		i++;
	}
}
