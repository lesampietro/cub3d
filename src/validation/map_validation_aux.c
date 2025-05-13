/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_aux.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:58:10 by lsampiet          #+#    #+#             */
/*   Updated: 2025/05/13 02:23:43 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				printf(BPINK"Error: invalid character <%c> in map\n"RST, data->map[i][j]);
				free_and_exit(data->game, EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

bool	is_map_border(char **map, int lin, int i, int j)
{
	if (i == 0 || i == lin - 1 || j == 0 || j == (int)ft_strlen(map[i]) - 1)
	{
		printf(BPINK "Error: map is not surrounded by walls \
				at x:%i, y:%i\n" RST, i, j);
		return (true);
	}
	if (map[i - 1][j] == ' ' || map[i + 1][j] == ' ')
	{
		printf(BPINK "Error: map is not surrounded by walls \
			at x:%i, y:%i\n" RST, i, j);
		return (true);
	}
	return (false);
}

void	check_element_on_edge(t_data *data, char c, int i, int j)
{
	if (data->map[i][j] == c)
	{
		if (is_map_border(data->map, data->lin, i, j))
			free_and_exit(data->game, EXIT_FAILURE);
		if (ft_isspace(data->map[i - 1][j]) || ft_isspace(data->map[i + 1][j]) \
			|| ft_isspace(data->map[i][j - 1]) \
			|| ft_isspace(data->map[i][j + 1]))
		{
			printf(BPINK "Error: map is not surrounded by walls \
				at y:%i, x:%i\n" RST, i, j);
			free_and_exit(data->game, EXIT_FAILURE);
		}
	}
}

void	is_surrounded_by_walls(t_data *data, char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_element_on_edge(data, '0', i, j);
			check_element_on_edge(data, 'S', i, j);
			check_element_on_edge(data, 'N', i, j);
			check_element_on_edge(data, 'E', i, j);
			check_element_on_edge(data, 'W', i, j);
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
				count++;
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
