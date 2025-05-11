#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

typedef struct s_game				t_game;
typedef struct s_data				t_data;
typedef struct s_raycasting			t_raycasting;
typedef struct s_keys				t_keys;
typedef struct s_vector				t_vector;
typedef struct s_coord				t_coord;
typedef struct s_wall				t_wall;
typedef struct s_element			t_element;
typedef struct s_weapon_render		t_weapon_render;
typedef struct s_sprite_draw		t_sprite_draw;
typedef struct s_element_raycast	t_element_raycast;

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

typedef enum e_element_id
{
	ENEMY = 1,
	HEALTH,
	ITEM,
	EXIT
}	t_element_id;

typedef enum e_dir
{
	NORTH,
	EAST,
	SOUTH,
	WEST
}	t_dir;

#endif