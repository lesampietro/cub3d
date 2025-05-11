#include "../includes/cub3d.h"

int32_t	main(int argc, char **argv)
{
	t_game			game;
	t_data			data;
	t_raycasting	raycasting;

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
