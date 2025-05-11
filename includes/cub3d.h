/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:52:23 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/11 17:11:26 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/time.h>
# include "../.lib/MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

// # define WINDOW_WIDTH 800
// # define WINDOW_HEIGHT 600
// # define WEAPON_SCALE 1.5

# define WINDOW_WIDTH 1900
# define WINDOW_HEIGHT 1200
# define WEAPON_SCALE 2.5

# define MOVE_SPEED 0.04
# define ROTATE_SPEED 2.8
# define SPRINT_MULTIPLIER 2

# define VERTICAL 0
# define HORIZONTAL 1

# define BPINK "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BRED "\033[1;31m"
# define BGRN "\033[1;32m"
# define RST "\033[0m"

typedef struct s_game		t_game;
typedef struct s_data		t_data;
typedef struct s_raycasting	t_raycasting;
typedef struct s_keys		t_keys;
typedef struct s_vector		t_vector;
typedef struct s_coord		t_coord;
typedef struct s_wall		t_wall;

typedef enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_dir;

typedef struct s_vector
{
	float	x;
	float	y;
}	t_vector;

typedef struct s_coord
{
	int		x;
	int		y;
}	t_coord;

# include "validation.h"
# include "engine.h"

typedef struct s_data
{
	t_game		*game;
	char		**map;
	int			fd;
	int			col;
	int			lin;
	char		*direction[4];
	int			*c;
	int			*f;
	char		pov;
	uint32_t	ceiling;
	uint32_t	floor;
}	t_data;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*mlx_image;
	mlx_texture_t	*texture_buf;
	mlx_texture_t	*texture[4];
	t_data			*data;
	t_raycasting	*raycasting;
	t_keys			keys;
	t_vector		player_pos;
	t_vector		player_dir;
	t_vector		camera_plane;
	int				hit_side;
}	t_game;

int32_t		init_game(char *argv, t_game *game);
void		init_window(t_game *game);

void		free_and_exit(t_game *game, int code);

#endif