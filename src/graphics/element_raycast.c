#include "../../includes/cub3d.h"

static bool	is_valid_element(t_element *element)
{
	return (element->alive && element->texture);
}

static void	draw_sprite_stripe(t_game *game, t_sprite_draw *draw_ctx)
{
	int	tex_height;
	int	y;
	int	d;
	int	tex_y;

	y = draw_ctx->raycast->draw_start_y;
	tex_height = draw_ctx->element->texture->height;
	while (y < draw_ctx->raycast->draw_end_y)
	{
		d = y * 256 - WINDOW_HEIGHT * 128 + draw_ctx->raycast->height * 128;
		tex_y = ((d * tex_height) / draw_ctx->raycast->height) / 256;
		uint32_t color = get_texture_pixel(draw_ctx->element->texture, draw_ctx->tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0)
		{
			game->raycasting->z_buffer[draw_ctx->stripe] = draw_ctx->raycast->transform_y;
			mlx_put_pixel(game->mlx_image, draw_ctx->stripe, y, color);
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

	tex_width = e->texture->width;
	printf("e->type = %d, e->texture = %p\n", e->type, (void *)e->texture);

	stripe = d->draw_start_x;
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
		else
			e->visible = false;
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

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].alive)
			render_element(game, i);
		i++;
	}
}
