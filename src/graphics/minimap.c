#include "../../includes/cub3d.h"

# define SIZE 8
# define IND 10

static void	fill_tile(mlx_image_t *image, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while (j < SIZE)
		{
			mlx_put_pixel(image, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static int	desloc(t_game *game, int y)
{
	int	desloc;
	desloc = (y * SIZE) - IND + WINDOW_HEIGHT - (game->data->lin * SIZE);
	return (desloc);
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
				while (pixel++ < SIZE)
					fill_tile(game->mlx_image, (j * SIZE) + IND, desloc(game, i),
						convert_rgb(220, 220, 220));
			}
			j++;
		}
		i++;
	}
	fill_tile(game->mlx_image, ((int)game->player_pos.x * SIZE) + IND,
		desloc(game, (int)game->player_pos.y), convert_rgb(255, 0, 0));
}
