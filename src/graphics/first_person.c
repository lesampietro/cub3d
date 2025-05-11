/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_person.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:54:02 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/10 23:54:03 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_scaled_pixel(t_weapon_render *ctx, int base_x,
	int base_y, uint32_t color)
{
	int	dx;
	int	dy;
	int	screen_x;
	int	screen_y;

	dx = 0;
	while (dx < WEAPON_SCALE)
	{
		dy = 0;
		while (dy < WEAPON_SCALE)
		{
			screen_x = base_x + dx;
			screen_y = base_y + dy;
			if (screen_x >= 0 && screen_x < WINDOW_WIDTH
				&& screen_y >= 0 && screen_y < WINDOW_HEIGHT)
			{
				mlx_put_pixel(ctx->game->mlx_image, screen_x, screen_y, color);
			}
			dy++;
		}
		dx++;
	}
}

static void	draw_texture_pixel(t_weapon_render *ctx, uint32_t x, uint32_t y)
{
	uint32_t	tex_x;
	uint32_t	tex_y;
	uint32_t	color;

	tex_x = ctx->texture->width - 1 - x;
	tex_y = y;
	color = get_texture_pixel(ctx->texture, tex_x, tex_y);
	if ((color & 0x00FFFFFF) != 0)
	{
		draw_scaled_pixel(ctx, (ctx->offset_x + x * WEAPON_SCALE),
			(ctx->offset_y + y * WEAPON_SCALE), color);
	}
}

void	render_weapon(t_game *game, mlx_texture_t *texture)
{
	t_weapon_render	ctx;
	uint32_t		x;
	uint32_t		y;

	ctx = (t_weapon_render){
		.game = game,
		.texture = texture,
		.offset_x = WINDOW_WIDTH / 2,
		.offset_y = WINDOW_HEIGHT / 2
	};
	x = 0;
	while (x < texture->width)
	{
		y = 0;
		while (y < texture->height)
		{
			draw_texture_pixel(&ctx, x, y);
			y++;
		}
		x++;
	}
}

void	draw_weapon(t_game *game)
{
	if (game->keys.mouse_left)
		render_weapon(game, game->weapon_shooting_texture);
	else
		render_weapon(game, game->weapon_texture);
}
