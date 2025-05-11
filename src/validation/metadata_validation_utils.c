#include "../../includes/cub3d.h"

bool	check_color(char *line)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	split = ft_split(line, ',');
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]))
			{
				printf(BPINK "Error: invalid colour info\n" RST);
				ft_free_split(split);
				return (false);
			}
			j++;
		}
		i++;
	}
	if (i != 3 || split[3])
	{
		printf(BPINK "Error: invalid colour info\n" RST);
		ft_free_split(split);
		return (false);
	}
	ft_free_split(split);
	return (true);
}

void	check_invalid_count(t_data *data, int count, char *line)
{
	if (count == 6)
	{
		if (data->direction[NORTH] && data->direction[SOUTH] \
			&& data->direction[EAST] && data->direction[WEST] \
			&& data->floor && data->ceiling)
			return ;
	}
	printf(BPINK"Error: missing or duplicated texture/colour info"RST);
	free(line);
	line = NULL;
	free_and_exit(data->game, 1);
}
