/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:53:56 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/10 23:53:57 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_valid_element(t_element *element)
{
	return (element->alive);
}

static void	draw_sprite_stripe(t_game *game, t_sprite_draw *draw_ctx)
{
	int	tex_height;
	int	y;
	int	d;
	int	tex_y;

	y = draw_ctx->raycast->draw_start_y;
	tex_height = draw_ctx->element->current_texture->height;
	while (y < draw_ctx->raycast->draw_end_y)
	{
		d = y * 256 - WINDOW_HEIGHT * 128 + draw_ctx->raycast->height * 128;
		tex_y = ((d * tex_height) / draw_ctx->raycast->height) / 256;
		if ((get_sprite_color(draw_ctx, tex_y) & 0x00FFFFFF) != 0)
		{
			if (draw_ctx->element->type == ENEMY)
			{
				game->raycasting->z_buffer[draw_ctx->stripe] = \
					draw_ctx->raycast->transform_y;
			}
			mlx_put_pixel(game->mlx_image, draw_ctx->stripe, y, \
				get_sprite_color(draw_ctx, tex_y));
		}
		y++;
	}
}

static void	render_sprite_stripes(t_game *game, t_element *e,
	t_element_raycast *d)
{
	int				tex_width;
	int				stripe;
	int				tex_x;
	t_sprite_draw	draw_ctx;

	tex_width = e->current_texture->width;
	stripe = d->draw_start_x;
	e->visible = false;
	while (stripe < d->draw_end_x)
	{
		tex_x = (int)(256 * (stripe + (d->width / 2) - d->screen_x)
				* tex_width / d->width) / 256;
		if (d->transform_y > 0 && stripe >= 0 && stripe < WINDOW_WIDTH
			&& d->transform_y < game->raycasting->z_buffer[stripe])
		{
			e->visible = true;
			draw_ctx = (t_sprite_draw){e, d, tex_x, stripe};
			draw_sprite_stripe(game, &draw_ctx);
		}
		stripe++;
	}
}

static void	render_element(t_game *game, int i)
{
	t_element			*e;
	t_element_raycast	d;

	e = &game->element[i];
	if (!is_valid_element(e))
		return ;
	compute_sprite_data(game, e, &d);
	if (d.transform_y <= 0)
		return ;
	render_sprite_stripes(game, e, &d);
}

void	render_elements(t_game *game)
{
	int	i;
	int	rank;

	rank = 0;
	i = 0;
	sort_elements(game);
	while (rank < game->element_count)
	{
		i = 0;
		while (i < game->element_count)
		{
			if (game->element[i].dist_rank == rank)
			{
				render_element(game, i);
				break ;
			}
			i++;
		}
		rank++;
	}
}
