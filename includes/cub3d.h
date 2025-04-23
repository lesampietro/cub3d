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

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define MOVE_SPEED 0.08
# define ROTATE_SPEED 3.5

# define VERTICAL 0
# define HORIZONTAL 1

# define PI 3.141592653589793

# define BPINK "\033[1;35m"
# define BCYAN "\033[1;36m"
# define RST "\033[0m"

typedef struct s_keys
{
	bool w;
	bool a;
	bool s;
	bool d;
	bool left;
	bool right;
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


typedef struct s_raycasting
{
	t_vector	direction;
	t_vector	delta_dist;
	t_vector	side_dist;
	t_vector	ray_dir;
	t_vector	camera_pixel;
	float		perp_wall_dist;
	float		plane_multiply;
	int			hit_side;
	t_coord		map_pos;
	t_coord		step;
}	t_raycasting;

typedef struct s_data
{
	char		**map;
	int			col;
	int			lin;
	char		*no;
	char		*so;
	char		*ea;
	char		*we;
	char		*c;
	char		*f;
	uint32_t	ceiling;
	uint32_t	floor;
} t_data;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*mlx_image;
	t_data			*data;
	t_raycasting	*raycasting;
	t_keys			keys;
	t_vector		player_pos;
	t_vector		player_dir;
	t_vector		camera_plane;
	int				hit_side;

} t_game;

typedef struct s_wall
{
	int		height;
	int		line_start;
	int		line_end;
	t_coord	texture;
	float	point;
}	t_wall;

int32_t			init_game(char *argv, t_game *game);
void			init_window(t_game *game);

//MAP VALIDATION
void			validate_map(int argc, char **argv, t_data *data);
void			is_valid_ext(char *file_ext);


//GRAPHICS
void		frame_loop(void *param);
void		draw_background(t_game *game, t_data *data);
void		draw_raycasting(t_game *game);
uint32_t	convert_rgb(int r, int g, int b);
t_vector	multiply_vector(t_vector vector, double factor);
t_vector	add_vector(t_vector vector1, t_vector vector2);
t_vector	rotate_vector(t_vector v, float angle);
void		draw_wall(t_game *game, t_raycasting *ray, int pixel);

//MOVEMENT
void		key_hook(mlx_key_data_t keydata, void *param);
void		move_player(t_game *game);

#endif