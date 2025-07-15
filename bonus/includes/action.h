/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:12:28 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 00:22:11 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

# define ENEMY_DAMAGE 11
# define ENEMY_ATKSPEED 1300

# define PLAYER_DAMAGE 50
# define POTION_HEALTH 25

# include "cub3d.h"

//MOVEMENT
void		key_hook(mlx_key_data_t keydata, void *param);
void		mouse_rotation(t_game *game);
void		move_player(t_game *game);
void		mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);

//ACTION
uint64_t	get_time_in_ms(void);
void		shoot_hit(t_game *game);
void		check_player_life(void *param);
void		objective_check(void *param);
void		detect_potion(t_game *game);
bool		is_close(t_game *game, int i);
//SHOOTING
bool		check_target(t_game *g, int i, int *hit_index, float *min_dist);
void		enemy_shots(t_game *game);
void		enemy_texture_reset(t_game *game);

void		reset_game(t_game *game);

#endif