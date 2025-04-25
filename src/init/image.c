#include "../../includes/cub3d.h"

void load_texture(t_game *game)
{
	int				i;

	i = 0;
	while (i < 4)
	{
		game->texture[i] = mlx_load_png(game->data->direction[i]);
		if (!game->texture[i])
		{
			printf("Error loading texture: %s\n", game->data->direction[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	game->enemy[0].texture = mlx_load_png(game->enemy[0].texture_path);
	if (!game->enemy[0].texture)
	{
		printf("Error loading enemy texture: %s\n", game->enemy[0].texture_path);
		exit(EXIT_FAILURE);
	}
}

void init_textures(t_game *game)
{
	game->data->direction[NORTH] = "./textures/pattern1.png";
	game->data->direction[SOUTH] = "./textures/pattern2.png";
	game->data->direction[EAST] = "./textures/pattern3.png";
	game->data->direction[WEST] = "./textures/pattern4.png";
	game->enemy[0].texture_path = "./assets/enemies/wizard idle.png";
	load_texture(game);
}

uint32_t get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
	int texture_pos;
	uint8_t	*pixel;

	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	texture_pos = y * texture->width + x;
	texture_pos *= texture->bytes_per_pixel;
	pixel = &texture->pixels[texture_pos];
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}