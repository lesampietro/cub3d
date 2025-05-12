/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objective.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:32 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/12 20:13:38 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	printf(BGRN"-------------------------------------\n"RST);
	printf(BGRN"|          MISSION COMPLETE         |\n"RST);
	printf(BGRN"-------------------------------------\n"RST);
	free_and_exit(game, 0);
}
