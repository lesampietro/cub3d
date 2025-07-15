/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:52:23 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 00:45:43 by nasser           ###   ########.fr       */
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
# define SENSITIVITY 0.02
# define SPRINT_MULTIPLIER 2

# define BPINK "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BRED "\033[1;31m"
# define BGRN "\033[1;32m"
# define RST "\033[0m"

# include "types.h"
# include "graphics.h"
# include "action.h"
# include "validation.h"

typedef struct s_element
{
	mlx_texture_t	*current_texture;
	mlx_texture_t	*shooting_texture;
	mlx_texture_t	*idle_texture;
	mlx_texture_t	*hit_texture;
	char			*texture_path;
	char			*hit_texture_path;
	char			*shooting_texture_path;
	char			*idle_texture_path;
	float			x;
	float			y;
	float			distance;
	int				health;
	int				type;
	int				dist_rank;
	int				id;
	bool			alive;
	bool			visible;
	bool			shooting;
	bool			got_hit;
	uint64_t		last_hit_time;
	uint64_t		last_shot_time;
	uint64_t		first_visible_time;
}	t_element;

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
	mlx_image_t		*phrase_image;
	mlx_image_t		*continue_phrase_image;
	mlx_image_t		*start_phrase_image;
	mlx_texture_t	*texture_buf;
	mlx_texture_t	*texture[4];
	mlx_texture_t	*weapon_texture;
	char			*weapon_text_path;
	mlx_texture_t	*weapon_shooting_texture;
	char			*weapon_shooting_text_path;
	char			*item_text_path;
	char			*idle_text_path;
	char			*shooting_text_path;
	char			*hit_text_path;
	char			*health_text_path;
	t_data			*data;
	t_raycasting	*raycasting;
	t_keys			keys;
	int				player_health;
	t_vector		player_initial_pos;
	t_vector		player_initial_dir;
	t_vector		player_initial_plane;
	t_vector		player_pos;
	t_vector		player_dir;
	t_vector		camera_plane;
	int				hit_side;
	int				mouse_prev_x;
	int				element_count;
	t_element		element[35];
	int				total_items;
	int				item_count;
	bool			minimap;
	bool			minimap_enemies;
	bool			menu_active;
	bool			game_won;
	bool			game_lost;
}	t_game;

int32_t		init_game(char *argv, t_game *game);
void		init_window(t_game *game);
void		init_elements(t_game *game);
void		free_and_exit(t_game *game, int code);

#endif