#include "../../includes/cub3d.h"

void	render_element(t_game *game, int i)
{
	t_element	*element;

	element = game->element;
	if (!element[i].alive || !element[i].texture)
		return;

	// Posição relativa ao jogador
	float sprite_x = element[i].x + 0.5f - game->player_pos.x;
	float sprite_y = element[i].y + 0.5f - game->player_pos.y;

	// Inverso da matriz de rotação da câmera
	float inv_det = 1.0f / (game->camera_plane.x * game->player_dir.y - game->player_dir.x * game->camera_plane.y);
	float transform_x = inv_det * (game->player_dir.y * sprite_x - game->player_dir.x * sprite_y);
	float transform_y = inv_det * (-game->camera_plane.y * sprite_x + game->camera_plane.x * sprite_y);

	if (transform_y <= 0)
		return;

	int sprite_screen_x = (int)((WINDOW_WIDTH / 2) * (1 + transform_x / transform_y));

	// Tamanho na tela proporcional à distância
	int sprite_height = abs((int)(WINDOW_HEIGHT / transform_y));
	int draw_start_y = -sprite_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start_y < 0) draw_start_y = 0;
	int draw_end_y = sprite_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end_y >= WINDOW_HEIGHT) draw_end_y = WINDOW_HEIGHT - 1;

	int sprite_width = sprite_height; // Mantém o sprite quadrado
	int draw_start_x = -sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0) draw_start_x = 0;
	int draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_end_x >= WINDOW_WIDTH) draw_end_x = WINDOW_WIDTH - 1;

	int tex_width = element[i].texture->width;
	int tex_height = element[i].texture->height;

	for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
	{
		int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * tex_width / sprite_width) / 256;

		// Verifica se está na frente da parede naquela coluna
		if (transform_y > 0 && stripe >= 0 && stripe < WINDOW_WIDTH &&
			transform_y < game->raycasting->z_buffer[stripe])
		{
			for (int y = draw_start_y; y < draw_end_y; y++)
			{
				int d = (y) * 256 - WINDOW_HEIGHT * 128 + sprite_height * 128;
				int tex_y = ((d * tex_height) / sprite_height) / 256;

				uint32_t color = get_texture_pixel(element[i].texture, tex_x, tex_y);

				if ((color & 0x00FFFFFF) != 0)
					mlx_put_pixel(game->mlx_image, stripe, y, color);
			}
		}
	}
}

void	render_elements(t_game *game)
{
	for (int i = 0; i < game->element_count; i++)
	{
		if (game->element[i].alive)
			render_element(game, i);
	}
}
