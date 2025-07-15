/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:12:32 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/07/15 00:06:04 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# define MAP_SIZE 8
# define MAP_IND 10

# define AIM_RADIUS 10
# define AIM_THICK 2

# define VERTICAL 0
# define HORIZONTAL 1

# define PI 3.141592653589793

# include "cub3d.h"

typedef struct s_sprite_draw
{
	t_element			*element;
	t_element_raycast	*raycast;
	int					tex_x;
	int					stripe;
}	t_sprite_draw;

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

// GRAPHICS
void		ui_init(t_game *game);
void		frame_loop(void *param);
void		draw_background(t_game *game, t_data *data);
void		fill_with_black(t_game *game);
void		draw_raycasting(t_game *game);
uint32_t	convert_rgb(int r, int g, int b);
t_vector	multiply_vector(t_vector vector, double factor);
t_vector	add_vector(t_vector vector1, t_vector vector2);
t_vector	rotate_vector(t_vector v, float angle);
t_vector	create_vector(float x, float y);
uint32_t	get_sprite_color(t_sprite_draw *draw_ctx, int tex_y);
void		draw_wall(t_game *game, t_raycasting *ray, int pixel);
void		init_textures(t_game *game);
uint32_t	get_texture_pixel(mlx_texture_t *texture, int x, int y);
void		draw_minimap(void *param);
void		draw_progress_bar(t_game *game);
void		draw_weapon(t_game *game);
void		render_elements(t_game *game);
void		compute_sprite_data(t_game *game, t_element *e,
				t_element_raycast *d);
void		sort_elements(t_game *game);
void		draw_game_finish(t_game *game);

#endif