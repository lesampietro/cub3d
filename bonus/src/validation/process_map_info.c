/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_info.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:58:27 by lsampiet          #+#    #+#             */
/*   Updated: 2025/05/10 23:58:28 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	fill_element_info(t_element *e)
{
	if (e->type == ENEMY)
	{
		e->idle_texture_path = "./assets/enemies/wizard idle.png";
		e->shooting_texture_path = "./assets/enemies/wizard attack3.png";
		e->hit_texture_path = "./assets/enemies/wizard_strucky.png";
	}
	else if (e->type == HEALTH)
	{
		e->health = POTION_HEALTH;
		e->idle_texture_path = "./assets/items/red_potion.png";
	}
	else if (e->type == ITEM)
		e->idle_texture_path = "./assets/items/key.png";
}

static void	process_element(t_data *data, int x, int y, char c)
{
	t_element	*e;

	e = &data->game->element[data->game->element_count];
	*e = (t_element){0};
	e->x = (float)x + 0.5f;
	e->y = (float)y + 0.5f;
	e->alive = true;
	e->id = data->game->element_count;
	e->health = 100;
	if (c == 'X')
		e->type = ENEMY;
	else if (c == 'I')
		e->type = ITEM;
	else if (c == 'H')
		e->type = HEALTH;
	fill_element_info(e);
	data->game->element_count++;
}

void	process_info(t_data *data)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x] != '\0')
		{
			c = data->map[y][x];
			if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
			{
				data->pov = c;
				data->game->player_pos.x = x + 0.5f;
				data->game->player_pos.y = y + 0.5f;
				data->map[y][x] = '0';
			}
			if (c == 'X' || c == 'I' || c == 'H')
				process_element(data, x, y, c);
			x++;
		}
		y++;
	}
}
