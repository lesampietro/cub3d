/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_raycast_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:54 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/10 23:53:55 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

uint32_t	get_sprite_color(t_sprite_draw *draw_ctx, int tex_y)
{
	uint32_t	color;

	color = get_texture_pixel(draw_ctx->element->current_texture,
			draw_ctx->tex_x, tex_y);
	return (color);
}

static void	get_sprite_transform(t_game *game, t_element *e,
	t_element_raycast *r)
{
	float	rel_x;
	float	rel_y;
	float	inv_det;

	rel_x = e->x - game->player_pos.x;
	rel_y = e->y - game->player_pos.y;
	inv_det = 1.0f / (game->camera_plane.x * game->player_dir.y
			- game->player_dir.x * game->camera_plane.y);
	r->transform_x = inv_det * (game->player_dir.y * rel_x
			- game->player_dir.x * rel_y);
	r->transform_y = inv_det * (-game->camera_plane.y * rel_x
			+ game->camera_plane.x * rel_y);
}

static void	clamp_draw_limits(int *start, int *end, int max)
{
	if (*start < 0)
		*start = 0;
	if (*end >= max)
		*end = max - 1;
}

void	compute_sprite_data(t_game *game, t_element *e, t_element_raycast *d)
{
	get_sprite_transform(game, e, d);
	if (d->transform_y <= 0)
		return ;
	d->screen_x = (int)((WINDOW_WIDTH / 2)
			* (1 + d->transform_x / d->transform_y));
	d->height = abs((int)(WINDOW_HEIGHT / d->transform_y));
	d->width = d->height;
	d->draw_start_y = -d->height / 2 + WINDOW_HEIGHT / 2;
	d->draw_end_y = d->height / 2 + WINDOW_HEIGHT / 2;
	clamp_draw_limits(&d->draw_start_y, &d->draw_end_y, WINDOW_HEIGHT);
	d->draw_start_x = -d->width / 2 + d->screen_x;
	d->draw_end_x = d->width / 2 + d->screen_x;
	clamp_draw_limits(&d->draw_start_x, &d->draw_end_x, WINDOW_WIDTH);
}
