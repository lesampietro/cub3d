#include "../includes/cub3d.h"

void init_values(t_game *game)
{
	game->map = NULL;
	game->mlx = NULL;
	game->col = 0;
	game->lin = 0;
	game->ceiling = convert_rgb(100, 149, 237);
    game->floor = convert_rgb(107, 180, 54);
	// game->icon = NULL;
	// game->pos.x = 0;
	// game->pos.y = 0;
}

int32_t main(int argc, char **argv)
{
	t_game game;

	init_values(&game);
	validate_map(argc, argv);
	// free_map(entry_map);
	// init_game(argv[1], &game);
	// return (EXIT_SUCCESS);
	(void)argc;
	return (EXIT_SUCCESS);
}