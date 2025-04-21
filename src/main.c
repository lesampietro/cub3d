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

char **get_map(void)
{
	static char **map = {
	"1111111111111",
	"1100001000011",
	"1000000000001",
	"100000S000001",
	"1000000000001",
	"1100001000011",
	"1000000000001",
	"1000000000001",
	"1000000000001",
	"1100001000011",
	"1111111111111",
	NULL
	};
	return (map);
}

int32_t main(int argc, char **argv)
{
	char **new_map;

	new_map = get_map();
	// int i;
	t_game game;

	init_values(&game);
	validate_map(argc, argv);
	// free_map(entry_map);
	// init_game(argv[1], &game);
	// return (EXIT_SUCCESS);
	(void)argc;
	return (EXIT_SUCCESS);
}