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

# define MAP_SIZE 8
# define MAP_IND 10

# define ENEMY_DAMAGE 11
# define PLAYER_DAMAGE 14
# define POTION_HEALTH 25

# define ENEMY_SHOOT_INTERVAL 1000
# define MOVE_SPEED 0.04
# define ROTATE_SPEED 2.8
# define SENSITIVITY 0.02
# define SPRINT_MULTIPLIER 2

# define VERTICAL 0
# define HORIZONTAL 1

# define PI 3.141592653589793

# define BPINK "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BRED "\033[1;31m"
# define BGRN "\033[1;32m"
# define RST "\033[0m"

typedef struct s_game t_game;
typedef struct s_data t_data;

typedef enum e_element_id
{
	ENEMY = 1,
	HEALTH,
	ITEM,
	EXIT
}	t_element_id;

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

typedef struct s_keys
{
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	left;
	bool	right;
	bool	shift;
	bool	mouse_left;
}	t_keys;

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

typedef struct s_element_raycast
{
	int		screen_x;
	int		width;
	int		height;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
	float	transform_x;
	float	transform_y;
}	t_element_raycast;

typedef struct s_sprite_draw
{
	t_element			*element;
	t_element_raycast	*raycast;
	int					tex_x;
	int					stripe;
}	t_sprite_draw;

typedef struct s_raycasting
{
	t_vector	direction;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	ray_dir;
	t_vector	camera_pixel;
	float		perp_wall_dist;
	float		z_buffer[WINDOW_WIDTH];
	float		plane_multiply;
	int			hit_side;
	t_coord		map_pos;
	t_coord		step;
}	t_raycasting;

typedef struct s_data
{
	t_game		*game;
	char		**map;
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
	mlx_texture_t	*weapon_texture;
	char			*weapon_text_path;
	mlx_texture_t	*weapon_shooting_texture;
	char			*weapon_shooting_text_path;
	t_data			*data;
	t_raycasting	*raycasting;
	t_keys			keys;
	int				player_health;
	t_vector		player_pos;
	t_vector		player_dir;
	t_vector		camera_plane;
	int				hit_side;
	int				mouse_prev_x;
	int				element_count;
	t_element		element[35];
	int				total_items;
	int				item_count;
}	t_game;

typedef struct s_weapon_render
{
	t_game			*game;
	mlx_texture_t	*texture;
	int				offset_x;
	int				offset_y;
}	t_weapon_render;

typedef struct s_wall
{
	int		height;
	int		line_start;
	int		line_end;
	t_coord	texture;
	float	resize;
	float	texture_pos;
	float	point;

}	t_wall;

typedef enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_dir;

int32_t		init_game(char *argv, t_game *game);
void		init_window(t_game *game);

//MAP VALIDATION
void		process_map(int argc, char **argv, t_data *data);
void		check_map_metadata(int fd, t_data *data, char **map_line);
int			safe_open(char *filename);
void		check_invalid_count(int count, t_data *data);
void		check_color(char *line);
char		*check_line_info(char *line);
void		find_map_first_line(int fd, char **map_line);

	// GRAPHICS
void		ui_init(t_game *game);
void		frame_loop(void *param);
void		draw_background(t_game *game, t_data *data);
void		draw_raycasting(t_game *game);
uint32_t	convert_rgb(int r, int g, int b);
t_vector	multiply_vector(t_vector vector, double factor);
t_vector	add_vector(t_vector vector1, t_vector vector2);
t_vector	rotate_vector(t_vector v, float angle);
t_vector	create_vector(float x, float y);
void		draw_wall(t_game *game, t_raycasting *ray, int pixel);
void		init_textures(t_game *game);
uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y);
void		draw_minimap(void *param);

void		draw_weapon(t_game *game);

void		render_elements(t_game *game);
void		compute_sprite_data(t_game *game, t_element *e,
				t_element_raycast *d);
void		sort_elements(t_game *game);

//MOVEMENT
void		key_hook(mlx_key_data_t keydata, void *param);
void		mouse_rotation(t_game *game);
void		move_player(t_game *game);
void		mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);

//ACTION
uint64_t	get_time_in_ms(void);
void		shoot_hit(t_game *game);
void		check_player_life(void *param);
void		objective_check(void *param);
// void		check_element_life(t_game *game);
void		detect_potion(t_game *game);
bool		is_close(t_game *game, int i);
//SHOOTING
bool		check_target(t_game *g, int i, int *hit_index, float *min_dist);
void		enemy_shots(t_game *game);
void		enemy_texture_reset(t_game *game);

//FREE
void		free_and_exit(t_game *game);

#endif