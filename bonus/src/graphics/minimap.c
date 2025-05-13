/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:54:06 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/13 15:15:36 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	fill_tile(mlx_image_t *image, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_SIZE)
	{
		j = 0;
		while (j < MAP_SIZE)
		{
			mlx_put_pixel(image, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	print_tile(t_game *game, t_coord coord, uint32_t color)
{
	int	i;
	int	desloc;

	desloc = (coord.y * MAP_SIZE) - MAP_IND + WINDOW_HEIGHT
		- (game->data->lin * MAP_SIZE);
	i = 0;
	while (i++ < MAP_SIZE)
		fill_tile(game->mlx_image, (coord.x * MAP_SIZE) + MAP_IND,
			desloc, color);
}

static void	found_element(t_game *game, t_coord coord)
{
	if (game->data->map[coord.y][coord.x] == '1')
		print_tile(game, coord, convert_rgb(255, 255, 255));
	else if (game->data->map[coord.y][coord.x] == 'X')
	{
		if (game->minimap_enemies)
			print_tile(game, coord, convert_rgb(255, 0, 0));
		else
			print_tile(game, coord, convert_rgb(0, 0, 0));
	}
	else if (game->data->map[coord.y][coord.x] == 'I')
		print_tile(game, coord, convert_rgb(20, 130, 255));
	else if (game->data->map[coord.y][coord.x] == 'H')
		print_tile(game, coord, convert_rgb(0, 255, 0));
	else
		print_tile(game, coord, convert_rgb(0, 0, 0));
}

void	draw_minimap(void *param)
{
	t_game	*game;
	t_coord	coord;

	coord = (t_coord){0, 0};
	game = (t_game *)param;
	while (game->data->map[coord.y])
	{
		coord.x = 0;
		while (game->data->map[coord.y][coord.x])
		{
			if (game->data->map[coord.y][coord.x] == '1' || \
				game->data->map[coord.y][coord.x] == 'X' || \
				game->data->map[coord.y][coord.x] == 'I' || \
				game->data->map[coord.y][coord.x] == 'H')
				found_element(game, coord);
			else if (game->data->map[coord.y][coord.x] == '0')
				print_tile(game, coord, convert_rgb(0, 0, 0));
			coord.x++;
		}
		coord.y++;
	}
	print_tile(game, (t_coord){(int)game->player_pos.x, \
		(int)game->player_pos.y},
		convert_rgb(255, 255, 0));
}
