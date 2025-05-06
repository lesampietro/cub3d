#include "../../includes/cub3d.h"

static void	fill_tile(mlx_image_t *image, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MAP_SIZE)
	{
		j = 0;
		while (j < MAP_SIZE)
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

	desloc = (y * MAP_SIZE) - MAP_IND + WINDOW_HEIGHT
		- (game->data->lin * MAP_SIZE);
	return (desloc);
}

void	print_element(t_game *game, t_coord coord, int pixel, uint32_t color)
{
	while (pixel++ < MAP_SIZE)
		fill_tile(game->mlx_image, (coord.x * MAP_SIZE) + MAP_IND,
			desloc(game, coord.y), color);
}

void	found_element(t_game *game, t_coord coord, int pixel)
{

	if (game->data->map[coord.y][coord.x] == '1')
		print_element(game, coord, pixel, convert_rgb(255, 255, 255));
	else if (game->data->map[coord.y][coord.x] == 'X')
		print_element(game, coord, pixel, convert_rgb(255, 0, 0));
	else if (game->data->map[coord.y][coord.x] == 'I')
		print_element(game, coord, pixel, convert_rgb(0, 0, 255));
	else if (game->data->map[coord.y][coord.x] == 'H')
		print_element(game, coord, pixel, convert_rgb(0, 255, 0));
}
void	draw_minimap(void *param)
{
	t_game	*game;
	// int		i;
	// int		j;
	t_coord	coord;
	int		pixel;
	
	coord = (t_coord){0, 0};
	game = (t_game *)param;
	// i = 0;
	while (game->data->map[coord.y])
	{
		coord.x = 0;
		while (game->data->map[coord.y][coord.x])
		{
			pixel = 0;
			if (game->data->map[coord.y][coord.x] == '1' || game->data->map[coord.y][coord.x] == 'X'
				|| game->data->map[coord.y][coord.x] == 'I' || game->data->map[coord.y][coord.x] == 'H')
				found_element(game, coord, pixel);
			coord.x++;
		}
		coord.y++;
	}
	fill_tile(game->mlx_image, ((int)game->player_pos.x * MAP_SIZE) + MAP_IND,
		desloc(game, (int)game->player_pos.y), convert_rgb(255, 255, 0));
}
