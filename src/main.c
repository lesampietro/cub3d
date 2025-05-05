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
	init_graphics(&game);

	// MOCK:
	// (void)argc;
	// data.map = get_map();
	// get_map_size(&data);

	game.player_health = 100;

	// game.element_count = 4;
	// ENEMY 1
	// game.element[0].x = 12.5;
	// game.element[0].y = 11.5;
	
	// game.element[0].alive = true;
	// game.element[0].health = 100;
	// game.element[0].type = ENEMY;
	// game.element[0].idle_texture_path = "./assets/enemies/wizard idle.png";
	// game.element[0].shooting_texture_path = "./assets/enemies/wizard attack2.png";
	// game.element[0].visible = false;
	// game.element[0].first_visible_time = 0;


	// // ENEMY 2
	// game.element[1].alive = true;
	// game.element[1].x = 14.5;
	// game.element[1].y = 11.5;
	// game.element[1].health = 100;
	// game.element[1].type = ENEMY;
	// game.element[1].idle_texture_path = "./assets/enemies/wizard idle.png";
	// game.element[1].shooting_texture_path = "./assets/enemies/wizard attack2.png";
	// game.element[1].visible = false;
	// game.element[1].first_visible_time = 0;

	// // ENEMY 3
	// game.element[2].alive = true;
	// game.element[2].x = 9.5;
	// game.element[2].y = 9.5;
	// game.element[2].health = 100;
	// game.element[2].type = ENEMY;
	// game.element[2].idle_texture_path = "./assets/enemies/wizard idle.png";
	// game.element[2].shooting_texture_path = "./assets/enemies/wizard attack2.png";
	// game.element[2].visible = false;
	// game.element[2].first_visible_time = 0;

	// // ITEM 1
	// game.element[3].alive = true;
	// game.element[3].x = 14.5;
	// game.element[3].y = 13.5;
	// game.element[3].health = 100;
	// game.element[3].type = ITEM;
	// game.element[3].texture_path = "./assets/items/health.png";
	// game.element[3].visible = false;
	// game.element[3].first_visible_time = 0;

	// game.player_pos.x = 1.5;
	// game.player_pos.y = 1.5;

	// game.player_dir.x = -1;
	// game.player_dir.y = 0;

	// game.camera_plane.x = 0;
	// game.camera_plane.y = -0.66;

	// PSYCHODELIC
	// data.ceiling = convert_rgb(147, 249, 23);
	// data.floor = convert_rgb(207, 18, 254);

	// DUNGEON
	// data.ceiling = convert_rgb(60, 30, 60);
	// data.floor = convert_rgb(60, 50, 55);

	// // MICROSOFT
	// // data.floor = convert_rgb(216, 137, 29);
	// // data.ceiling = convert_rgb(218, 218, 218);


	// game.data->pov = 'S';
	init_game(argv[1], &game);
	return (EXIT_SUCCESS);
}
