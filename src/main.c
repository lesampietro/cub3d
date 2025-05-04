#include "../includes/cub3d.h"

uint32_t	convert_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

// void init_values(t_data *data)
// {
// 	data->map = NULL;
// 	data->col = 0;
// 	data->lin = 0;
// 	data->no = NULL;
// 	data->so = NULL;
// 	data->ea = NULL;
// 	data->we = NULL;
// 	data->ceiling = NULL;
// 	data->floor = NULL;
// 	// game->icon = NULL;
// 	// game->pos.x = 0;
// 	// game->pos.y = 0;
// }
// game->ceiling = 0xFF006872;
// game->floor = 0xFF4B0082;

char **get_map(void)
{
	// static char *map[] = {
	// 	"1111111111111",
	// 	"1100001000011",
	// 	"1000000000001",
	// 	"100100S001001",
	// 	"1000000000001",
	// 	"1100001000011",
	// 	"1000000000001",
	// 	"1000000000001",
	// 	"1000000000001",
	// 	"1100001000011",
	// 	"1111111111111",
	// };

	// static char *map[] = {
	// 	"1111111111111111111",
	// 	"1000001000001000001",
	// 	"1011111011111011101",
	// 	"1010000010000000101",
	// 	"1010111110111111101",
	// 	"1010000010100000001",
	// 	"1011111010111111011",
	// 	"1000001010000010001",
	// 	"1111101011111011111",
	// 	"1000001000100000001",
	// 	"1011111110111111101",
	// 	"1000000000000000001",
	// 	"1111111111111111111",
	// 	NULL
	// };

	static char *map[] = {
		"1111111111111111111111111111",
		"1000000000001000000000000101",
		"1011111000000011111111100101",
		"1000000000010100000100000101",
		"1010111010010111100101011101",
		"1010000010000000000101000001",
		"1010111110000011111001000101",
		"1000001000000000000001000101",
		"1000001000000000000001000101",
		"1000000000100000000000000101",
		"1000100000000000000111110101",
		"1000100000000000000100000101",
		"1110100000000000000111100101",
		"1000100000000000000000010101",
		"1000000000000000000000000101",
		"1010000000000100000100010101",
		"1010000000000000000101110101",
		"1010100000000101000100000101",
		"1010101111111111000111111101",
		"1010101000000001000000000001",
		"1010101111111111000111111111",
		"1000101000010000000000000001",
		"1111111111111111111111111111",
		NULL
	};

	return (map);
}

void get_map_size(t_data *data)
{
	int i;

	i = 0;
	while (data->map[i])
		i++;
	data->lin = i;
	data->col = ft_strlen(data->map[0]);
}

int32_t main(int argc, char **argv)
{
	t_game			game;
	t_data			data;
	t_raycasting 	raycasting;
	
	game = (t_game){0};
	data = (t_data){0};
	raycasting = (t_raycasting){0};
	game.data = &data;
	game.raycasting = &raycasting;
	validate_map(argc, argv, &data);

	// MOCK:
	data.map = get_map();
	get_map_size(&data);

	game.player_health = 100;

	game.element_count = 4;
	// ENEMY 1
	game.element[0].alive = true;
	game.element[0].x = 12.5;
	game.element[0].y = 11.5;
	game.element[0].health = 100;
	game.element[0].type = ENEMY;
	game.element[0].idle_texture_path = "./assets/enemies/wizard idle.png";
	game.element[0].shooting_texture_path = "./assets/enemies/wizard attack2.png";
	game.element[0].visible = false;
	game.element[0].first_visible_time = 0;


	// ENEMY 2
	game.element[1].alive = true;
	game.element[1].x = 14.5;
	game.element[1].y = 11.5;
	game.element[1].health = 100;
	game.element[1].type = ENEMY;
	game.element[1].idle_texture_path = "./assets/enemies/wizard idle.png";
	game.element[1].shooting_texture_path = "./assets/enemies/wizard attack2.png";
	game.element[1].visible = false;
	game.element[1].first_visible_time = 0;

	// ENEMY 3
	game.element[2].alive = true;
	game.element[2].x = 9.5;
	game.element[2].y = 9.5;
	game.element[2].health = 100;
	game.element[2].type = ENEMY;
	game.element[2].idle_texture_path = "./assets/enemies/wizard idle.png";
	game.element[2].shooting_texture_path = "./assets/enemies/wizard attack2.png";
	game.element[2].visible = false;
	game.element[2].first_visible_time = 0;

	// ITEM 1
	game.element[3].alive = true;
	game.element[3].x = 14.5;
	game.element[3].y = 13.5;
	game.element[3].health = 100;
	game.element[3].type = ITEM;
	game.element[3].texture_path = "./assets/items/health.png";
	game.element[3].visible = false;
	game.element[3].first_visible_time = 0;

	game.player_pos.x = 1.5;
	game.player_pos.y = 1.5;


	// PSYCHODELIC
	// data.ceiling = convert_rgb(147, 249, 23);
	// data.floor = convert_rgb(207, 18, 254);

	// MICROSOFT
	// data.floor = convert_rgb(216, 137, 29);
	// data.ceiling = convert_rgb(218, 218, 218);

	game.data->pov = 'S';
	init_game(argv[1], &game);
	return (EXIT_SUCCESS);
}
