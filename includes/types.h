#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

typedef struct s_game			t_game;
typedef struct s_data			t_data;
typedef struct s_raycasting		t_raycasting;
typedef struct s_keys			t_keys;
typedef struct s_wall			t_wall;

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

#endif