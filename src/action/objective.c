#include "../../includes/cub3d.h"

void	detect_item(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->element_count)
	{
		if (game->element[i].type == ITEM && game->element[i].health > 0 && is_close(game, i) )
		{	
			game->element[i].health = 0;
			game->element[i].alive = false;
			game->item_count++;
			game->data->map[(int)game->element[i].y][(int)game->element[i].x] = '0';
			break ;
		}
		i++;
	}
}

void	objective_check(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	detect_item(game);
	if (game->item_count < game->total_items)
		return ;
	printf(BGRN"-------------------------------------\n"RST);
	printf(BGRN"| You collected all items! You win! |\n"RST);
	printf(BGRN"-------------------------------------\n"RST);
	free_and_exit(game, 0);
	// return ;
}