#include "../../includes/cub3d.h"

void load_texture(t_game *game)
{
	int				i;

	i = 0;
	game->weapon_texture = mlx_load_png(game->weapon_text_path);
	game->weapon_shooting_texture = mlx_load_png(game->weapon_shooting_text_path);
	if (!game->weapon_texture || !game->weapon_shooting_texture)
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
		if (!game->element[i].idle_texture_path)
    		printf("idle_texture_path is NULL for element %i\n", i);
		// if (!game->element[i].shooting_texture_path)
    	// 	printf("shooting_texture_path is NULL for element %i\n", i);
			// TEST


		if (game->element[i].type == ENEMY)
		{
			game->element[i].idle_texture = mlx_load_png(game->element[i].idle_texture_path);
			game->element[i].shooting_texture = mlx_load_png(game->element[i].shooting_texture_path);
			game->element[i].hit_texture = mlx_load_png(game->element[i].hit_texture_path);
			game->element[i].current_texture = game->element[i].idle_texture;
			if (!game->element[i].idle_texture || !game->element[i].shooting_texture || !game->element[i].hit_texture)
			{
				printf("Error loading texture for ENEMY element: %i\n", i);
				exit(EXIT_FAILURE);
			}
		}
		else if (game->element[i].type == ITEM)
		{
			game->element[i].idle_texture = mlx_load_png(game->element[i].idle_texture_path);
			game->element[i].current_texture = game->element[i].idle_texture;
			if (!game->element[i].idle_texture)
			{
				printf("Error loading texture for ITEM element: %i\n", i);
				exit(EXIT_FAILURE);
			}
		}
		else if (game->element[i].type == HEALTH)
		{
			game->element[i].idle_texture = mlx_load_png(game->element[i].idle_texture_path);
			game->element[i].current_texture = game->element[i].idle_texture;
			if (!game->element[i].idle_texture)
			{
				printf("Error loading texture for HEALTH element: %i\n", i);
				exit(EXIT_FAILURE);
			}
		}

		i++;
	}
}

void init_textures(t_game *game)
{
	game->weapon_shooting_text_path = "./assets/wand_shooting.png";
	game->weapon_text_path = "./assets/wand.png";
	// init_elements(game);
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