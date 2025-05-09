#include "../../includes/cub3d.h"

static void	draw_bar_outline(t_game *game, int start_x, int start_y)
{
	int	x;
	int	y;
	int	inner_start_x;
	int	inner_end_x;

	inner_start_x = start_x + 4;
	inner_end_x = start_x + 204;
	y = start_y;
	while (y < start_y + 23)
	{
		x = start_x;
		while (x < start_x + 208)
		{
			if (x < inner_start_x || x >= inner_end_x || \
				y < start_y + 4 || y >= start_y + 19)
				mlx_put_pixel(game->mlx_image, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

static void	draw_bar_fill(t_game *game, int start_x, int start_y)
{
	int		x;
	int		y;
	int		filled_width;
	float	filled_ratio;

	filled_ratio = (float)game->item_count / (float)game->total_items;
	filled_width = (int)(200 * filled_ratio);
	y = start_y + 4;
	while (y < start_y + 19)
	{
		x = start_x + 4;
		while (x < start_x + 4 + filled_width)
		{
			mlx_put_pixel(game->mlx_image, x, y, convert_rgb(250, 206, 15));
			x++;
		}
		y++;
	}
}

static void	draw_division_line(t_game *game, int div_x, int start_y, int end_y)
{
	int	x;
	int	y;
	int	draw_x;
	int	inner_start_x;

	inner_start_x = (WINDOW_WIDTH - 208) / 2 + 4;
	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < 5)
		{
			draw_x = div_x + x;
			if (draw_x >= inner_start_x && draw_x < inner_start_x + 200)
				mlx_put_pixel(game->mlx_image, draw_x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

static void	draw_division_lines(t_game *game, int start_x, int start_y)
{
	int	i;
	int	sector_width;
	int	division_x;
	int	inner_start_x;

	inner_start_x = start_x + 4;
	sector_width = 200 / game->total_items;
	i = 1;
	while (i < game->total_items)
	{
		division_x = inner_start_x + i * sector_width - 2;
		draw_division_line(game, division_x, start_y + 4, start_y + 19);
		i++;
	}
}

void	draw_progress_bar(t_game *game)
{
	int	start_x;
	int	start_y;

	start_x = (WINDOW_WIDTH - 208) / 2;
	start_y = 40;
	draw_bar_outline(game, start_x, start_y);
	draw_bar_fill(game, start_x, start_y);
	draw_division_lines(game, start_x, start_y);
}
