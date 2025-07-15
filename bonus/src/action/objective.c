/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objective.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:32 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 01:02:58 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/action.h"

static void	detect_item(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].type == ITEM && game->element[i].health
			> 0 && is_close(game, i))
		{
			game->element[i].health = 0;
			game->element[i].alive = false;
			game->item_count++;
			game->data->map[(int)game->element[i].y]
			[(int)game->element[i].x] = '0';
			break ;
		}
		i++;
	}
}

int	count_enemies(t_game *game)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < game->element_count)
	{
		if (game->element[i].type == ENEMY && game->element[i].health > 0)
			count++;
		i++;
	}
	return (count);
}

static bool	are_all_enemys_dead(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].type == ENEMY && game->element[i].health > 0)
			return (false);
		i++;
	}
	return (true);
}

void reset_game(t_game *game)
{
	int i;

	i = 0;
	while (i < game->element_count)
	{
		game->element[i].alive = true;
		if (game->element[i].type == ENEMY)
			game->element[i].health = 100;
		else if (game->element[i].type == ITEM)
			game->element[i].health = 100;
		else if (game->element[i].type == HEALTH)
			game->element[i].health = POTION_HEALTH;
		i++;
	}
	game->player_health = 100;
	game->item_count = 0;
	game->game_won = false;
	game->game_lost = false;
	game->player_health = 100;
	// game->player_pos.x = game->player_initial_pos.x;
	// game->player_pos.y = game->player_initial_pos.y;
	game->player_dir = game->player_initial_dir;
	game->camera_plane = game->player_initial_plane;
	game->player_pos = game->player_initial_pos;

	// game->menu_active = true;
}

void	objective_check(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	detect_item(game);
	if (count_enemies(game) == 0 && game->item_count == 0)
		return ;
	if (!are_all_enemys_dead(game))
		return ;
	if (game->item_count < game->total_items)
		return ;
	if (game->phrase_image)
		mlx_delete_image(game->mlx, game->phrase_image);
	game->phrase_image = mlx_put_string(game->mlx, "DUNGEON COMPLETE", WINDOW_WIDTH / 2 - 65, WINDOW_HEIGHT / 2 - 10);
	if (game->continue_phrase_image)
		mlx_delete_image(game->mlx, game->continue_phrase_image);
	game->continue_phrase_image = mlx_put_string(game->mlx, "Press ENTER to continue", WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT - WINDOW_HEIGHT / 10);
	game->game_won = true;
}
