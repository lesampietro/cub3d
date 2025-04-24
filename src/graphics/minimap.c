#include "../../includes/cub3d.h"

# define MINIMAP_SIZE 5

void	fill_tile(mlx_image_t *image, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			mlx_put_pixel(image, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(void *param)
{
	t_game	*game;
	int		i;
	int		j;
	int		pixel;

	game = (t_game *)param;
	i = 0;
	while (game->data->map[i])
	{
		j = 0;
		while (game->data->map[i][j])
		{
			pixel = 0;
			if (game->data->map[i][j] == '1')
			{
				while (pixel++ < MINIMAP_SIZE)
					fill_tile(game->mlx_image, j * MINIMAP_SIZE, i * MINIMAP_SIZE, convert_rgb(255, 255, 255));
			}
			else if (game->data->map[i][j] == '0')
			{
				while (pixel++ < MINIMAP_SIZE)
					fill_tile(game->mlx_image, j * MINIMAP_SIZE, i * MINIMAP_SIZE, convert_rgb(0, 0, 0));
			}
			j++;
		}
		i++;
	}
	fill_tile(game->mlx_image, (int)game->player_pos.x * MINIMAP_SIZE, (int)game->player_pos.y * MINIMAP_SIZE, convert_rgb(255, 0, 0));
}