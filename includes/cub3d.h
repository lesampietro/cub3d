#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include <stdint.h>
# include <stdbool.h>
# include "../.lib/MLX42/include/MLX42/MLX42.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_game
{
	char		**map;
	mlx_t		*mlx;
	int			col;
	int			lin;
} t_game;

int32_t	init_game(char *argv, t_game *game);
void	init_window(t_game *game);

//MAP VALIDATION
void    validate_map(char   **argv);
bool	is_invalid_extn(char **file_ext);


#endif