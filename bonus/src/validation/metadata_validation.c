/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metadata_validation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:58:24 by lsampiet          #+#    #+#             */
/*   Updated: 2025/05/10 23:58:25 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*check_line_info(char *line)
{
	char	**split;
	char	*path;

	split = NULL;
	line = ft_strtrim(line, " \n");
	split = ft_split(line, ' ');
	free(line);
	path = NULL;
	if (split[2])
		ft_free_split(split);
	else if (split[1])
	{
		path = ft_strdup(split[1]);
		ft_free_split(split);
		return (path);
	}
	else
		ft_free_split(split);
	return (NULL);
}

static void	is_empty_file(char *line)
{
	while (line && ft_isspace(*line))
		line++;
	if (!line)
	{
		printf(BPINK"Error: file is empty\n"RST);
		free(line);
		line = NULL;
		exit(EXIT_FAILURE);
	}
}

static void	check_invalid_count(t_data *data, int count, char *line)
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

bool	is_map_line(char *line)
{
	int		i;
	bool	map;

	i = 0;
	map = false;
	if (ft_strchr(line, '1'))
	{
		while (ft_isspace(line[i]))
			i++;
		while (line[i] && line[i] != '\n')
		{
			if (line[i] == '1' || line[i] == '0' || ft_isspace(line[i])
				|| line[i] == 'S' || line[i] == 'N' || line[i] == 'E'
				|| line[i] == 'W' || line[i] == 'X' || line[i] == 'I'
				|| line[i] == 'H')
				map = true;
			else
			{
				map = false;
				break ;
			}
			i++;
		}
	}
	return (map);
}

void	check_map_metadata(t_data *data, char **map_line)
{
	int		count;

	count = 0;
	*map_line = get_next_line(data->fd);
	is_empty_file(*map_line);
	while (*map_line)
	{
		if (is_map_line(*map_line))
			break ;
		if (!read_textures_n_colours(&count, *map_line, data))
		{
			free(*map_line);
			*map_line = NULL;
			free_and_exit(data->game, EXIT_FAILURE);
		}
		free(*map_line);
		*map_line = get_next_line(data->fd);
	}
	check_invalid_count(data, count, *map_line);
	if (*map_line)
	{
		free(*map_line);
		*map_line = NULL;
	}
	close(data->fd);
}
