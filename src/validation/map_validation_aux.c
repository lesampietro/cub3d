#include "../../includes/cub3d.h"

void	check_map_info(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		if (is_empty_line_in_map(data->map, i))
		{
			printf(BPINK"Error: empty line in map\n"RST);
			free_and_exit(data->game, EXIT_FAILURE);
		}
		while (data->map[i][j])
		{
			if (!is_valid_char(data->map[i][j]))
			{
				printf(BPINK"Error: invalid character in map\n"RST);
				free_and_exit(data->game, EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

int	count_items(t_data *data)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'I')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

bool	is_map_border(char **map, int lin, int i, int j)
{
	if (i == 0 || i == lin - 1 || j == 0 || j == (int)ft_strlen(map[i]) - 1)
	{
		printf(BPINK "Error: map is not surrounded by walls at x:%i, y:%i\n" RST, i, j);
		return (true);
	}
	if (!map[i - 1][j] || !map[i + 1][j])
	{
			printf(BPINK "Error: map is not surrounded by walls at x:%i, y:%i\n" RST, i, j);
			return (true);
	}
	return (false);
}

void	is_surrounded_by_walls(t_data *data, char **map, int lin)
{
	int		i;
	int		j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (is_map_border(map, lin, i, j))
					free_and_exit(data->game, EXIT_FAILURE);
				if (ft_isspace(map[i - 1][j]) || ft_isspace(map[i + 1][j]) \
					|| ft_isspace(map[i][j - 1]) || ft_isspace(map[i][j + 1]))
				{
					printf(BPINK"Error: map is not surrounded by walls at x:%i, y:%i\n" RST, i, j);
					free_and_exit(data->game, EXIT_FAILURE);
				}
			}
			j++;
		}
		i++;
	}
}

void	check_map_elements(t_data *data, char **map)
{
	int		i;
	int		j;
	int		count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' \
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				map[i][j] = '0';
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		printf(BPINK"Error: invalid number of player positions\n"RST);
		free_and_exit(data->game, EXIT_FAILURE);
	}
}
