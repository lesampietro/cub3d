/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:58:14 by lsampiet          #+#    #+#             */
/*   Updated: 2025/05/11 15:43:02 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	safe_malloc(t_data *data, void **to_malloc, int size)
{
	*to_malloc = malloc(size);
	if (!*to_malloc)
	{
		printf("Error: memory allocation failed\n");
		free_and_exit(data->game, EXIT_FAILURE);
	}
}

int	safe_open(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf(BPINK"Error: failed to open file\n"RST);
		free_and_exit(data->game, EXIT_FAILURE);
	}
	return (fd);
}

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' \
		|| c == 'S' || c == 'N' || c == 'E' || c == 'W');
}

bool	is_empty_line_in_map(char **line, int i)
{
	int		c;

	c = 0;
	if (line[i][c] == '\0')
	{
		while (line[i])
		{
			c = 0;
			while (line[i][c] && ft_isspace(line[i][c]))
				c++;
			if (line[i][c] != '\0')
				return (true);
			i++;
		}
	}
	return (false);
}

