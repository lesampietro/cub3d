#include "../../includes/cub3d.h"

static void render_weapon(t_game *game, mlx_texture_t *texture)
{
	uint32_t x;
	uint32_t y;

	int offset_x;
	int offset_y;

	offset_x = WINDOW_WIDTH  / 2;
	offset_y = WINDOW_HEIGHT / 2;
	x = 0;
	while (x < texture->width)
	{
		y = 0;
		while (y < texture->height)
		{
			uint32_t color = get_texture_pixel(texture, texture->width - 1 - x, y);
			if ((color & 0x00FFFFFF) != 0)
			{
				int dx = 0;
				while (dx < WEAPON_SCALE)
				{
					int dy = 0;
					while (dy < WEAPON_SCALE)
					{
						int screen_x = offset_x + x * WEAPON_SCALE + dx;
						int screen_y = offset_y + y * WEAPON_SCALE + dy;
	
						if (screen_x >= 0 && screen_x < WINDOW_WIDTH &&
							screen_y >= 0 && screen_y < WINDOW_HEIGHT)
						{
							mlx_put_pixel(game->mlx_image, screen_x, screen_y, color);
						}
						dy++;
					}
					dx++;
				}
			}
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
