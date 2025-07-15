/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_shots.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:10 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 00:09:21 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	update_enemy_animation(t_element *enemy)
{
	uint64_t	now;

	if (enemy->shooting)
	{
		now = get_time_in_ms();
		if (now - enemy->last_shot_time >= 500)
		{
			enemy->current_texture = enemy->idle_texture;
			enemy->shooting = false;
		}
	}
}

void	enemy_shoot_at_player(t_game *game, t_element *enemy)
{
	if (enemy->visible)
	{
		enemy->current_texture = enemy->shooting_texture;
		game->player_health -= ENEMY_DAMAGE;
		enemy->shooting = true;
	}
}

void	update_enemy_shooting(t_game *game, t_element *enemy)
{
	uint64_t	now;

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
	if (now - enemy->first_visible_time < ENEMY_ATKSPEED)
		return ;
	if (now - enemy->last_shot_time >= ENEMY_ATKSPEED)
	{
		if (game->menu_active || game->game_won || game->game_lost)
			return ;
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
			update_enemy_animation(&game->element[i]);
			update_enemy_shooting(game, &game->element[i]);
		}
		i++;
	}
}
