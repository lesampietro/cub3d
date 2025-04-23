#include "../../includes/cub3d.h"

int	get_direction(float dir)
{
	if (dir < 0)
		return (-1);
	return (1);
}

void	delta_distance(t_raycasting *ray)
{
	if (ray->ray_dir.x == 0)
		ray->delta_dist.x = HUGE_VALF;
	else
		ray->delta_dist.x = fabsf(1 / ray->ray_dir.x);
	if (ray->ray_dir.y == 0)
		ray->delta_dist.y = HUGE_VALF;
	else
		ray->delta_dist.y = fabsf(1 / ray->ray_dir.y);
}

void	side_distance(t_game *game, t_raycasting *ray)
{
	ray->map_pos.x = game->player_pos.x;
	ray->map_pos.y = game->player_pos.y;
	if (ray->ray_dir.x < 0)
		ray->side_dist.x = (game->player_pos.x - ray->map_pos.x) * ray->delta_dist.x;
	else
	{
		ray->side_dist.x = (ray->map_pos.x + 1.0 - game->player_pos.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
		ray->side_dist.y = (game->player_pos.y - ray->map_pos.y) * ray->delta_dist.y;
	else
	{
		ray->side_dist.y = (ray->map_pos.y + 1.0 - game->player_pos.y) * ray->delta_dist.y;
	}
}

void	dda(t_game *game, t_raycasting *ray)
{
	while(game->data->map[ray->map_pos.y][ray->map_pos.x] != '1')
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->map_pos.x += ray->step.x;
			ray->hit_side = VERTICAL;
			game->hit_side = VERTICAL;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->map_pos.y += ray->step.y;
			ray->hit_side = HORIZONTAL;
			game->hit_side = HORIZONTAL;
		}
	}
	if(ray->hit_side == VERTICAL)
		ray->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

void	draw_raycasting(t_game *game)
{
	int	pix;
	t_raycasting	*ray;

	ray = game->raycasting;
	pix = 0;
	while (pix < WINDOW_WIDTH)
	{
		ray->plane_multiply = (2 * pix) / (float)WINDOW_WIDTH - 1;
		ray->camera_pixel = multiply_vector(game->camera_plane, ray->plane_multiply);
		ray->ray_dir = add_vector(game->player_dir, ray->camera_pixel);
		ray->step.x = get_direction(ray->ray_dir.x);
		ray->step.y = get_direction(ray->ray_dir.y);
		delta_distance(ray);
		side_distance(game, ray);
		dda(game, ray);
		draw_wall(game, ray, pix);
		pix++;	
	}
}