#include "../../includes/cub3d.h"

void load_texture(t_game *game)
{
	int				i;

	i = 0;
	game->weapon_texture = mlx_load_png(game->weapon_text_path);
	if (!game->weapon_texture)
	{
		printf("Error loading texture: %s\n", game->weapon_text_path);
		exit(EXIT_FAILURE);
	}
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
	i = 0;
	while (i < game->element_count)
	{
		game->element[i].texture = mlx_load_png(game->element[i].texture_path);
		if (!game->element[i].texture)
		{
			printf("Error loading element texture: %s\n", game->element[i].texture_path);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	// game->element[0].texture = mlx_load_png(game->element[0].texture_path);
	// if (!game->element[0].texture)
	// {
	// 	printf("Error loading element texture: %s\n", game->element[0].texture_path);
	// 	exit(EXIT_FAILURE);
	// }
}

void init_textures(t_game *game)
{
	game->data->direction[NORTH] = "./assets/textures/50 Free Stylized Wall Textures/1-16/Asset 3.png";
	game->data->direction[EAST] = "./assets/textures/50 Free Stylized Wall Textures/17-32/Asset 2.png";
	game->data->direction[SOUTH] = "./assets/textures/50 Free Stylized Wall Textures/1-16/Asset 6.png";
	game->data->direction[WEST] = "./assets/textures/50 Free Stylized Wall Textures/17-32/Asset 2.png";

	game->weapon_text_path = "./assets/wand_shooting.png";
	// game->data->direction[NORTH] = "./assets/textures/Torment Textures/True Colour/str_metalpan8.png";
	// game->data->direction[EAST] = "./assets/textures/Torment Textures/True Colour/str_metalgen4.png";
	// game->data->direction[SOUTH] = "./assets/textures/Torment Textures/True Colour/str_metalgrbl4.png";
	// game->data->direction[WEST] = "./assets/textures/Torment Textures/True Colour/str_metalgen6.png";
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