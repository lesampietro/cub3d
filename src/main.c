#include "../includes/cub3d.h"

void init_values(t_game *game)
{
	game->map = NULL;
	game->mlx = NULL;
	game->col = 0;
	game->lin = 0;
	// game->icon = NULL;
	// game->pos.x = 0;
	// game->pos.y = 0;
}

int32_t main(int argc, char **argv)
{
	t_game game;

	init_values(&game);
	if (argc != 2)
	{
		printf("Wrong number of arguments: needs only a map");
		return (EXIT_FAILURE);
	}
	// ft_error(ERROR_ARG, NULL);
	// is_valid_entry(&argv[1]);
	validate_map(argv);
	// free_map(entry_map);
	// init_game(argv[1], &game);
	// return (EXIT_SUCCESS);
	(void)argc;
	return (EXIT_SUCCESS);
}