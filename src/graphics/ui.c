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
            if (x < inner_start_x || x >= inner_end_x || 
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

static void	draw_progress_bar(t_game *game)
{
    int	start_x;
    int	start_y;

    start_x = (WINDOW_WIDTH - 208) / 2;
    start_y = 40;
    draw_bar_outline(game, start_x, start_y);
    draw_bar_fill(game, start_x, start_y);
    draw_division_lines(game, start_x, start_y);
}

// static void	draw_progress_bar(t_game *game)
// {
// 	int	x, y;
// 	int	start_x = (WINDOW_WIDTH - 208) / 2;
// 	int	start_y = 40;
// 	int	inner_start_x = start_x + 4;
// 	int	inner_end_x = start_x + 204;
// 	int	inner_start_y = start_y + 4;
// 	int	inner_end_y = start_y + 19;

// 	float filled_ratio = (float)game->item_count / (float)game->total_items;
// 	int	filled_width = (int)(200 * filled_ratio);
// 	int	sector_width = 200 / game->total_items;

// 	y = start_y;
// 	while (y < start_y + 23)
// 	{
// 		x = start_x;
// 		while (x < start_x + 208)
// 		{
// 			if (x < inner_start_x || x >= inner_end_x || y < inner_start_y || y >= inner_end_y)
// 				mlx_put_pixel(game->mlx_image, x, y, 0xFFFFFFFF); // contorno branco
// 			else if (x < inner_start_x + filled_width)
// 				mlx_put_pixel(game->mlx_image, x, y, convert_rgb(250,206,15)); // azul (progresso)
// 			// else
// 			// 	mlx_put_pixel(game->mlx_image, x, y, 0x00000000); // transparente ou vazio
// 			x++;
// 		}
// 		y++;
// 	}

// 	// Linhas de divisão entre setores (de 5px de largura)
// 	for (int i = 1; i < game->total_items; i++)
// 	{
// 		int division_x = inner_start_x + i * sector_width - 2; // -2 para centralizar os 5px
// 		for (y = inner_start_y; y < inner_end_y; y++)
// 		{
// 			for (x = 0; x < 5; x++)
// 			{
// 				int draw_x = division_x + x;
// 				if (draw_x >= inner_start_x && draw_x < inner_end_x)
// 					mlx_put_pixel(game->mlx_image, draw_x, y, 0xFFFFFFFF); // linha divisória branca
// 			}
// 		}
// 	}
// }

static void	draw_aim_circle(t_game *game)
{
	int		x;
	int 	y;
	float	distance;

	y = WINDOW_HEIGHT / 2 - AIM_RADIUS - AIM_THICK;
    while (y <= WINDOW_HEIGHT / 2 + AIM_RADIUS + AIM_THICK)
    {
		x = WINDOW_WIDTH / 2 - AIM_RADIUS - AIM_THICK;
        while (x <= WINDOW_WIDTH / 2 + AIM_RADIUS + AIM_THICK)
        {
            distance = sqrtf((x - WINDOW_WIDTH / 2) * (x - WINDOW_WIDTH / 2) + 
                                  (y - WINDOW_HEIGHT / 2) * (y - WINDOW_HEIGHT / 2));
            if (distance >= AIM_RADIUS - AIM_THICK/2 && distance <= AIM_RADIUS + AIM_THICK/2)
            {
                if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
                    mlx_put_pixel(game->mlx_image, x, y, convert_rgb(255,255,0));
            }
			x++;
        }
		y++;
    }
	mlx_put_pixel(game->mlx_image, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, convert_rgb(255, 255, 0));
}

static void	draw_health_bar(t_game *game)
{
	int	x, y;

	y = 10;
	while (y < 10 + 23)
	{
		x = (WINDOW_WIDTH - 208) / 2;
		while (x < (WINDOW_WIDTH - 208) / 2 + 208)
		{
			if (x < (WINDOW_WIDTH - 208) / 2 + 4 || x >= (WINDOW_WIDTH - 208) / 2 + 204
			 || y < 10 + 4 || y >= 10 + 19)
				mlx_put_pixel(game->mlx_image, x, y, convert_rgb(255, 255, 255));
			else if (x < (WINDOW_WIDTH - 208) / 2 + 4 + (int)(200 * (game->player_health / 100.0)))
				mlx_put_pixel(game->mlx_image, x, y, convert_rgb(255, 0, 0));
			x++;
		}
		y++;
	}
}

void	ui_init(t_game *game)
{
	draw_health_bar(game);
	draw_progress_bar(game);
	draw_aim_circle(game);
}