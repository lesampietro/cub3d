#include "../includes/cub3d.h"

// void init_values(t_game *game)
// {
// 	game->map = NULL;
// 	game->mlx = NULL;
// 	game->col = 0;
// 	game->lin = 0;
// 	game->icon = NULL;
// 	game->player_pos.x = 0;
// 	game->player_pos.y = 0;
// 	game->end_game = 1;
// 	game->steps = 0;
// }

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

	// i = 0;
	// init_values(&game);
	// if (argc != 2)
	// 	ft_error(ERROR_ARG, NULL);
	// is_valid_entry(&argv[1]);
	// new_map = read_map(argv[1]);
	// is_valid_map(new_map);
	// free_map(new_map);
	init_game(argv[1], &game);
	// return (EXIT_SUCCESS);
	(void)argc;
	return (EXIT_SUCCESS);
}