#ifndef ENGINE_H
# define ENGINE_H

# include "cub3d.h"

# define PI 3.141592653589793

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

// GRAPHICS
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

//MOVEMENT
void		key_hook(mlx_key_data_t keydata, void *param);
void		mouse_rotation(t_game *game);
void		move_player(t_game *game);
void		mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);

#endif