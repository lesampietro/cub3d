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
	static char *map[] = {
		"1111111111111",
		"1100001000011",
		"1000000000001",
		"100100S001001",
		"1000000000001",
		"1100001000011",
		"1000000000001",
		"1000000000001",
		"1000000000001",
		"1100001000011",
		"1111111111111",
	};
	return (map);
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
	// init_values(&data);
	// validate_map(argc, argv, &data);

	// MOCK:
	(void)argc;
	data.map = get_map();
	data.col = 13;
	data.lin = 11;
	game.player_pos.x = 6.5;
	game.player_pos.y = 3.5;

	game.player_dir.x = 1;
	game.player_dir.y = 0;

	game.camera_plane.x = 0;
	game.camera_plane.y = 0.66;

	data.ceiling = convert_rgb(100, 149, 237);
	data.floor = convert_rgb(107, 180, 54);


	init_game(argv[1], &game);
	return (EXIT_SUCCESS);
}