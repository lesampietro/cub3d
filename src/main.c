#include "../includes/cub3d.h"

uint32_t	convert_rgb(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

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
// game->ceiling = 0xFF006872;
// game->floor = 0xFF4B0082;

char **get_map(void)
{
	static char *map[] = {
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
	// if (argc != 2)
	// 	printf("Wrong number of arguments: needs only a map");
	
		// ft_error(ERROR_ARG, NULL);
	// is_valid_entry(&argv[1]);
	// validate_map(&argv[1]);
	// free_map(entry_map);
	init_game(argv[1], &game);
	// return (EXIT_SUCCESS);
	(void)argc;
	return (EXIT_SUCCESS);
}