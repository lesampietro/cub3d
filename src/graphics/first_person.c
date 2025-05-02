#include "../../includes/cub3d.h"

#define SCALE 2

void	draw_weapon(t_game *game)
{
	uint32_t x;
	uint32_t y;

	int offset_x;
	int offset_y;

	offset_x = (WINDOW_WIDTH - game->weapon_texture->width) / 2 + 120;
	offset_y = WINDOW_HEIGHT - game->weapon_texture->height - 200;
	x = 0;
	while (x < game->weapon_texture->width)
	{
		y = 0;
		while (y < game->weapon_texture->height)
		{
			uint32_t color = get_texture_pixel(game->weapon_texture, game->weapon_texture->width - 1 - x, y);

			// Se tiver transparência, ignora o pixel
			if ((color & 0x00FFFFFF) != 0) // ou ((color >> 24) & 0xFF > 0) se preferir
			{
				// Desenha bloco SCALE x SCALE na tela
				int dx = 0;
				while (dx < SCALE)
				{
					int dy = 0;
					while (dy < SCALE)
					{
						int screen_x = offset_x + x * SCALE + dx;
						int screen_y = offset_y + y * SCALE + dy;
	
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