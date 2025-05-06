#include "../../includes/cub3d.h"

# include <sys/time.h>

// void	damage_animation(t_game *game);
// nao funcionando ainda

uint64_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	update_enemy_animation(t_element *enemy)
{
	uint64_t now;

	if (enemy->shooting)
	{
		now = get_time_in_ms();
		if (now - enemy->last_shot_time >= 500)
		{
			enemy->current_texture = enemy->idle_texture;
			enemy->shooting = false;
		}
	}
}

void	enemy_shoot_at_player(t_game *game, t_element *enemy)
{
	if (enemy->visible)
	{
		enemy->current_texture = enemy->shooting_texture;
		game->player_health -= 5;
		enemy->shooting = true;
		// damage_animation(game);
	}
}

void	update_enemy_shooting(t_game *game, t_element *enemy)
{
	uint64_t now;

	now = get_time_in_ms();
	if (!enemy->alive)
		return ;
	if (!enemy->visible)
		enemy->first_visible_time = 0;
	if (enemy->first_visible_time == 0)
	{
		enemy->first_visible_time = now;
		return ;
	}
	if (now - enemy->first_visible_time < ENEMY_SHOOT_INTERVAL)
		return ;
	if (now - enemy->last_shot_time >= ENEMY_SHOOT_INTERVAL)
	{
		enemy_shoot_at_player(game, enemy);
		enemy->last_shot_time = now;
	}
}

void	enemy_shots(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].alive && game->element[i].type == ENEMY)
		{
			update_enemy_animation(&game->element[i]);
			update_enemy_shooting(game, &game->element[i]);
		}
		i++;
	}
}


// void	damage_animation(t_game *game)
// {
// 	const int thickness = 10;
// 	const uint32_t color = 0x88FF0000; // vermelho com transparência suave (88 = ~50%)

// 	int x, y;

// 	// Topo
// 	for (y = 0; y < thickness; y++)
// 		for (x = 0; x < WINDOW_WIDTH; x++)
// 			mlx_put_pixel(game->mlx_image, x, y, color);

// 	// Base
// 	for (y = WINDOW_HEIGHT - thickness; y < WINDOW_HEIGHT; y++)
// 		for (x = 0; x < WINDOW_WIDTH; x++)
// 			mlx_put_pixel(game->mlx_image, x, y, color);

// 	// Esquerda
// 	for (y = thickness; y < WINDOW_HEIGHT - thickness; y++)
// 		for (x = 0; x < thickness; x++)
// 			mlx_put_pixel(game->mlx_image, x, y, color);

// 	// Direita
// 	for (y = thickness; y < WINDOW_HEIGHT - thickness; y++)
// 		for (x = WINDOW_WIDTH - thickness; x < WINDOW_WIDTH; x++)
// 			mlx_put_pixel(game->mlx_image, x, y, color);
// }
