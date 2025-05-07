#include "../includes/cub3d.h"

uint32_t	convert_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
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
	data.game = &game;
	game.raycasting = &raycasting;
	process_map(argc, argv, &data);
	init_textures(&game);

	init_game(argv[1], &game);
	return (EXIT_SUCCESS);
}

/*       MOCK DATA
	char *map[] = {"1,1,1,1,1,1,1,1",
					"1,0,0,0,0,0,0,1",
					"1,0,0,0,0,0,0,1",
					"1,0,0,0,0,0,0,1",
					"1,0,0,0,0,0,0,1",
					"1,1,1,1,1,1,1,1",
					NULL};
	(void)argc;
	data.map = map;
	data.col = 8;
	data.lin = 6;
	game.player_pos.x = 3.5;
	game.player_pos.y = 3.5;
	game.player_dir.x = 1;
	game.player_dir.y = 0;
	game.camera_plane.x = 0;
	game.camera_plane.y = 0.66;
	game.player_health = 100;
	game.total_items = 1;
	game.element[0].type = ITEM;
	game.element[0].x = 4.5;
	game.element[0].y = 3.5;
	game.element[0].health = 100;
	game.element[0].idle_texture_path = "./assets/items/resource.png";
	data.direction[0] = "./assets/textures/walls/17-32/Asset2.png";
	data.direction[1] = "./assets/textures/walls/17-32/Asset6.png";
	data.direction[2] = "./assets/textures/walls/17-32/Asset2.png";
	data.direction[3] = "./assets/textures/walls/17-32/Asset6.png";
*/