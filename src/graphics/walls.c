#include "../../includes/cub3d.h"

void render(t_game *game, t_wall *wall, int pixel)
{
	int y;

	y = wall->line_start;
	while (y < wall->line_end)
	{
		if (game->hit_side == VERTICAL)
		{
			if (pixel % 2 == 0)
				mlx_put_pixel(game->mlx_image, pixel, y, 0xFF83B4FF);
			else
				mlx_put_pixel(game->mlx_image, pixel, y, 0xFF1C5C8E);
		}
		else
		{
			if (pixel % 2 == 0)
				mlx_put_pixel(game->mlx_image, pixel, y, 0xFF605257);
			else
				mlx_put_pixel(game->mlx_image, pixel, y, 0xFF16140C);
		}
		y++;
	}
}

void draw_wall(t_game *game, t_raycasting *ray, int pixel)
{
	t_wall	wall;

	wall = (t_wall){0};
	wall.height = (WINDOW_HEIGHT / ray->perp_wall_dist);
	wall.line_start = (WINDOW_HEIGHT / 2) - (wall.height / 2);
	wall.line_end = (WINDOW_HEIGHT / 2) + (wall.height / 2);
	if (wall.line_start < 0)
		wall.line_start = 0;
	if (wall.line_end >= WINDOW_HEIGHT)
		wall.line_end = WINDOW_HEIGHT - 1;
	render(game, &wall, pixel);
}
