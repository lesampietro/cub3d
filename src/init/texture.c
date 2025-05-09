#include "../../includes/cub3d.h"

static void	load_weapon_textures(t_game *game)
{
	game->weapon_texture = mlx_load_png(game->weapon_text_path);
	game->weapon_shooting_texture = \
		mlx_load_png(game->weapon_shooting_text_path);
	if (!game->weapon_texture || !game->weapon_shooting_texture)
	{
		printf("Error loading weapon textures\n");
		exit(EXIT_FAILURE);
	}
}

static void	load_wall_textures(t_game *game)
{
	int	i;

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
}

static void	load_enemy_textures(t_element *element)
{
	element->idle_texture = mlx_load_png(element->idle_texture_path);
	element->shooting_texture = mlx_load_png(element->shooting_texture_path);
	element->hit_texture = mlx_load_png(element->hit_texture_path);
	element->current_texture = element->idle_texture;
	if (!element->idle_texture || !element->shooting_texture || \
		!element->hit_texture)
	{
		printf("Error loading texture for ENEMY element\n");
		exit(EXIT_FAILURE);
	}
}

static void	load_pickup_textures(t_element *element, int type)
{
	element->idle_texture = mlx_load_png(element->idle_texture_path);
	element->current_texture = element->idle_texture;
	if (!element->idle_texture)
	{
		if (type == ITEM)
			printf("Error loading texture for ITEM element\n");
		else
			printf("Error loading texture for HEALTH element\n");
		exit(EXIT_FAILURE);
	}
}

void	init_textures(t_game *game)
{
	int	i;

	i = 0;
	game->weapon_shooting_text_path = "./assets/wand_shooting.png";
	game->weapon_text_path = "./assets/wand.png";
	load_weapon_textures(game);
	load_wall_textures(game);
	while (i < game->element_count)
	{
		if (game->element[i].type == ENEMY)
			load_enemy_textures(&game->element[i]);
		else if (game->element[i].type == ITEM)
			load_pickup_textures(&game->element[i], ITEM);
		else if (game->element[i].type == HEALTH)
			load_pickup_textures(&game->element[i], HEALTH);
		i++;
	}
}
