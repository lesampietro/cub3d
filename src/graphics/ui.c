#include "../../includes/cub3d.h"

#define AIM_RADIUS 10
#define AIM_THICK 2

static void	draw_progress_bar(t_game *game)
{
	int	x, y;
	int	start_x = (WINDOW_WIDTH - 208) / 2;
	int	start_y = 40; // um pouco abaixo da barra de vida
	int	inner_start_x = start_x + 4;
	int	inner_end_x = start_x + 204;
	int	inner_start_y = start_y + 4;
	int	inner_end_y = start_y + 19;

	float filled_ratio = (float)game->item_count / (float)game->total_items;
	int	filled_width = (int)(200 * filled_ratio);
	int	sector_width = 200 / game->total_items;

	y = start_y;
	while (y < start_y + 23)
	{
		x = start_x;
		while (x < start_x + 208)
		{
			if (x < inner_start_x || x >= inner_end_x || y < inner_start_y || y >= inner_end_y)
				mlx_put_pixel(game->mlx_image, x, y, 0xFFFFFFFF); // contorno branco
			else if (x < inner_start_x + filled_width)
				mlx_put_pixel(game->mlx_image, x, y, convert_rgb(250,206,15)); // azul (progresso)
			// else
			// 	mlx_put_pixel(game->mlx_image, x, y, 0x00000000); // transparente ou vazio
			x++;
		}
		y++;
	}

	// Linhas de divisão entre setores (de 5px de largura)
	for (int i = 1; i < game->total_items; i++)
	{
		int division_x = inner_start_x + i * sector_width - 2; // -2 para centralizar os 5px
		for (y = inner_start_y; y < inner_end_y; y++)
		{
			for (x = 0; x < 5; x++)
			{
				int draw_x = division_x + x;
				if (draw_x >= inner_start_x && draw_x < inner_end_x)
					mlx_put_pixel(game->mlx_image, draw_x, y, 0xFFFFFFFF); // linha divisória branca
			}
		}
	}
}

// static void	draw_aim_circle(t_game *game)
// {
// 	int		x;
// 	int 	y;
// 	float	distance;

// 	y = WINDOW_HEIGHT / 2 - AIM_RADIUS - AIM_THICK;
//     while (y <= WINDOW_HEIGHT / 2 + AIM_RADIUS + AIM_THICK)
//     {
// 		x = WINDOW_WIDTH / 2 - AIM_RADIUS - AIM_THICK;
//         while (x <= WINDOW_WIDTH / 2 + AIM_RADIUS + AIM_THICK)
//         {
//             distance = sqrtf((x - WINDOW_WIDTH / 2) * (x - WINDOW_WIDTH / 2) + 
//                                   (y - WINDOW_HEIGHT / 2) * (y - WINDOW_HEIGHT / 2));
//             if (distance >= AIM_RADIUS - AIM_THICK/2 && distance <= AIM_RADIUS + AIM_THICK/2)
//             {
//                 if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
//                     mlx_put_pixel(game->mlx_image, x, y, convert_rgb(255,255,0));
//             }
// 			x++;
//         }
// 		y++;
//     }
// 	mlx_put_pixel(game->mlx_image, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, convert_rgb(255, 255, 0));
// }

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
	draw_progress_bar(game);
	// draw_aim_circle(game);
}