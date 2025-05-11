/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_sorting.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:59 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/10 23:54:00 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	rank_elem_dist(t_game *game, int i)
{
	t_element	*e;
	float		dx;
	float		dy;

	e = &game->element[i];
	dx = e->x - game->player_pos.x;
	dy = e->y - game->player_pos.y;
	e->distance = dx * dx + dy * dy;
}

static void	swap_indices(int *indices, int i, int j)
{
	int	tmp;

	tmp = indices[i];
	indices[i] = indices[j];
	indices[j] = tmp;
}

static void	bubble_sort_indices(t_game *game, int *indices)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->element_count - 1)
	{
		j = i + 1;
		while (j < game->element_count)
		{
			if (game->element[indices[i]].distance
				< game->element[indices[j]].distance)
				swap_indices(indices, i, j);
			j++;
		}
		i++;
	}
}

void	sort_elements(t_game *game)
{
	int	i;
	int	indices[20];

	i = 0;
	while (i < game->element_count)
	{
		rank_elem_dist(game, i);
		indices[i] = i;
		i++;
	}
	bubble_sort_indices(game, indices);
	i = 0;
	while (i < game->element_count)
	{
		game->element[indices[i]].dist_rank = i;
		i++;
	}
}
