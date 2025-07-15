/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:14 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 00:52:54 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_close(t_game *game, int i)
{
	float	dx;
	float	dy;

	dx = game->element[i].x - game->player_pos.x;
	dy = game->element[i].y - game->player_pos.y;
	game->element[i].distance = dx * dx + dy * dy;
	if (game->element[i].distance < 1.0f)
		return (true);
	return (false);
}

void	detect_potion(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].type == HEALTH && game->element[i].health > 0
			&& is_close(game, i))
		{
			game->player_health += game->element[i].health;
			game->element[i].health = 0;
			game->element[i].alive = false;
			game->data->map[(int)game->element[i].y]
			[(int)game->element[i].x] = '0';
			break ;
		}
		i++;
	}
}

void	check_player_life(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	detect_potion(game);
	if (game->player_health > 100)
		game->player_health = 100;
	if (game->player_health > 0)
		return ;
	game->player_health = 0;
	if (game->phrase_image)
		mlx_delete_image(game->mlx, game->phrase_image);
	game->phrase_image = mlx_put_string(game->mlx, "GAME OVER", WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2 - 10);
	if (game->continue_phrase_image)
		mlx_delete_image(game->mlx, game->continue_phrase_image);
	game->continue_phrase_image = mlx_put_string(game->mlx, "Press ENTER to continue", WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT - WINDOW_HEIGHT / 10);
	game->game_lost = true;
	return ;
}
