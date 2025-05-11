/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:54:16 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/10 23:54:17 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

mlx_texture_t	*grab_texture(t_game *game)
{
	if (game->raycasting->hit_side == HORIZONTAL)
	{
		if (game->raycasting->step.y < 0)
			return (game->texture[NORTH]);
		else
			return (game->texture[SOUTH]);
	}
	else
	{
		if (game->raycasting->step.x < 0)
			return (game->texture[WEST]);
		else
			return (game->texture[EAST]);
	}
	return (NULL);
}

static void	hit_point(t_game *game, t_wall *wall)
{
	if (game->raycasting->hit_side == VERTICAL)
	{
		wall->point = game->player_pos.y + game->raycasting->perp_wall_dist
			* game->raycasting->ray_dir.y;
	}
	else
	{
		wall->point = game->player_pos.x + game->raycasting->perp_wall_dist
			* game->raycasting->ray_dir.x;
	}
	wall->point -= floor(wall->point);
}

static void	get_texture_point(t_game *game, t_wall *wall)
{
	wall->texture.x = (int)(wall->point * game->texture_buf->width);
	if ((game->raycasting->hit_side == VERTICAL && \
			game->raycasting->direction.x < 0) || \
			(game->hit_side == HORIZONTAL && game->raycasting->direction.y > 0))
		wall->texture.x = game->texture_buf->width - wall->texture.x - 1;
	wall->resize = 1.0 * game->texture_buf->height / wall->height;
}

void	render(t_game *game, t_wall *wall, int pixel)
{
	int			y;
	int			texture_y_pos;
	uint32_t	color;

	y = wall->line_start;
	while (y < wall->line_end)
	{
		texture_y_pos = (int)wall->texture_pos;
		if (texture_y_pos < 0)
			texture_y_pos = 0;
		if (texture_y_pos >= (int)game->texture_buf->height)
			texture_y_pos = game->texture_buf->height - 1;
		wall->texture_pos += wall->resize;
		color = get_texture_pixel(game->texture_buf, \
			wall->texture.x, texture_y_pos);
		mlx_put_pixel(game->mlx_image, pixel, y, color);
		y++;
	}
}

void	draw_wall(t_game *game, t_raycasting *ray, int pixel)
{
	t_wall	wall;

	wall = (t_wall){0};
	game->texture_buf = grab_texture(game);
	wall.height = (WINDOW_HEIGHT / ray->perp_wall_dist);
	wall.line_start = (WINDOW_HEIGHT / 2) - (wall.height / 2);
	wall.line_end = (WINDOW_HEIGHT / 2) + (wall.height / 2);
	if (wall.line_start < 0)
		wall.line_start = 0;
	if (wall.line_end >= WINDOW_HEIGHT)
		wall.line_end = WINDOW_HEIGHT - 1;
	hit_point(game, &wall);
	get_texture_point(game, &wall);
	wall.texture_pos = (wall.line_start - WINDOW_HEIGHT \
		/ 2 + wall.height / 2) * wall.resize;
	render(game, &wall, pixel);
}
