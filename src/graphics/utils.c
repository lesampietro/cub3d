#include "../../includes/cub3d.h"

t_vector	multiply_vector(t_vector vector, double factor)
{
	t_vector	result;

	result.x = vector.x * factor;
	result.y = vector.y * factor;
	return (result);
}

t_vector	add_vector(t_vector vector1, t_vector vector2)
{
	t_vector	result;

	result.x = vector1.x + vector2.x;
	result.y = vector1.y + vector2.y;
	return (result);
}

t_vector	rotate_vector(t_vector v, float angle)
{
	t_vector	vector;
	float		rad;

	rad = angle * PI / 180.0;
	vector.x = v.x * cos(rad) - v.y * sin(rad);
	vector.y = v.x * sin(rad) + v.y * cos(rad);
	return (vector);
}