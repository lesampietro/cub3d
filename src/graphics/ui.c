#include "../../includes/cub3d.h"

static void	draw_health_bar(t_game *game)
{
	int	x, y;

	y = 10;
	while (y < 10 + 23) // 15 (barra) + 2*4 (contorno)
	{
		x = (WINDOW_WIDTH - 208) / 2;
		while (x < (WINDOW_WIDTH - 208) / 2 + 208) // 200 barra + 2*4 contorno
		{
			if (x < (WINDOW_WIDTH - 208) / 2 + 4 || x >= (WINDOW_WIDTH - 208) / 2 + 204
			 || y < 10 + 4 || y >= 10 + 19)
				mlx_put_pixel(game->mlx_image, x, y, 0xFFFFFFFF); // branco (contorno)
			else if (x < (WINDOW_WIDTH - 208) / 2 + 4 + (int)(200 * (game->player_health / 100.0)))
				mlx_put_pixel(game->mlx_image, x, y, 0xFF0000FF); // vermelho (vida)
			x++;
		}
		y++;
	}
}

void	ui_init(t_game *game)
{
	draw_health_bar(game);
}