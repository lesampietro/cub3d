#include "../../includes/cub3d.h"

void	process_element(t_data *data, int x, int y, char c)
{
	t_game		*game = data->game;
	t_element	*e;
	
	if (game->element_count >= 34)
	{
		printf(BPINK"Error: too many elements in the map. Max = 35\n"RST);
		exit(EXIT_FAILURE);
	}
	
	e = &game->element[game->element_count];
	e->x = (float)x + 0.5f; // centraliza na célula
	e->y = (float)y + 0.5f;
	e->alive = true;
	e->visible = false;
	e->last_shot_time = 0;
	e->first_visible_time = 0;
	e->dist_rank = 0;
	e->distance = 0;
	e->id = game->element_count;
	e->got_hit = false;
	e->shooting = false;
	e->shooting_texture_path = NULL;
	e->hit_texture_path = NULL;
	e->texture_path = NULL;
	
	if (c == 'X')
	{
		e->type = ENEMY;
		e->health = 100;
		e->idle_texture_path = "./assets/enemies/wizard idle.png";
		e->shooting_texture_path = "./assets/enemies/wizard attack3.png";
		e->hit_texture_path = "./assets/enemies/wizard_strucky.png";
		e->texture_path = NULL;
		// e->got_hit = false;
		// e->shooting = false;
	}
	else if (c == 'I')
	{
		e->type = ITEM;
		e->health = 100;
		e->idle_texture_path = "./assets/items/key.png";
		// e->idle_texture_path = "./textures/rat.png";
		e->texture_path = NULL;
	}
	else if (c == 'H')
	{
		e->type = HEALTH;
		e->health = POTION_HEALTH;
		e->idle_texture_path = "./assets/items/red_potion.png";
		e->texture_path = NULL;
	}
	game->element_count++;
}

void	process_info(char *map_line, t_data *data, int map_index)
{
	int		x;
	char	c;

	x = 0;
	while (map_line[x] != '\0')
	{
		c = map_line[x];
		if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
		{
			data->pov = c;
			data->game->player_pos.x = x + 0.5f; // centraliza na célula
			data->game->player_pos.y = map_index + 0.5f;
		}
		if (c == 'X' || c == 'I' || c == 'H')
			process_element(data, x, map_index, c);
		x++;
	}

}