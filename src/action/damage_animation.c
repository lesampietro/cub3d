#include "../../includes/cub3d.h"

// void	start_damage_animation(t_game *game)
// {
// 	game->dmg_time_start = get_time_in_ms();
// 	game->show_dmg = true;
// }


// void	damage_animation(t_game *game)
// {
// 	if (!game->show_dmg)
// 		return ;
// 	if (get_time_in_ms() - game->dmg_time_start > 1000)
// 	{
// 		game->show_dmg = false;
// 		return ;
// 	}

// 	const int thickness = 10;
// 	const uint32_t color = 0x88FF0000; // vermelho escuro com ~50% opacidade

// 	int x, y;

// 	// Topo
// 	for (y = 0; y < thickness; y++)
// 		for (x = 0; x < WINDOW_WIDTH; x++)
// 			mlx_put_pixel(game->mlx_image, x, y, color);

// 	// Base
// 	for (y = WINDOW_HEIGHT - thickness; y < WINDOW_HEIGHT; y++)
// 		for (x = 0; x < WINDOW_WIDTH; x++)
// 			mlx_put_pixel(game->mlx_image, x, y, color);

// 	// Esquerda
// 	for (y = thickness; y < WINDOW_HEIGHT - thickness; y++)
// 		for (x = 0; x < thickness; x++)
// 			mlx_put_pixel(game->mlx_image, x, y, color);

// 	// Direita
// 	for (y = thickness; y < WINDOW_HEIGHT - thickness; y++)
// 		for (x = WINDOW_WIDTH - thickness; x < WINDOW_WIDTH; x++)
// 			mlx_put_pixel(game->mlx_image, x, y, color);
// }
