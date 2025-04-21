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
# include "../libft/libft.h"

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

#define BPINK "\033[1;35m"
#define BCYAN "\033[1;36m"
#define RST "\033[0m"

typedef struct s_game
{
	char		**map;
	mlx_t		*mlx;
	int			col;
	int			lin;
} t_game;

int32_t			init_game(char *argv, t_game *game);
void			init_window(t_game *game);

//MAP VALIDATION
void    		validate_map(int argc, char   **argv);
void			is_valid_ext(char 	*file_ext);


#endif