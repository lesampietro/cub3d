/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_save_metadata.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:58:31 by lsampiet          #+#    #+#             */
/*   Updated: 2025/05/11 17:00:14 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	check_texture(char *tmp)
{
	if (!tmp)
	{
		printf(BPINK "Error: invalid texture/colour info\n" RST);
		return (false);
	}
	if (ft_strncmp("./", tmp, 2) != 0)
	{
		printf(BPINK "Error: invalid texture path\n" RST);
		return (false);
	}
	return (true);
}

static bool	save_texture_path(char *line, char **path, int *count)
{
	char	*tmp;

	printf(BPINK "Saving texture path: %s\n" RST, line);
	tmp = check_line_info(line);
	if (!check_texture(tmp))
	{
		free(tmp);
		return (false);
	}
	if (!*path)
		*path = strdup(tmp);
	else
	{
		printf(BPINK "Error: Duplicated texture\n" RST);
		free(tmp);
		return (false);
	}
	(*count)++;
	free(tmp);
	return (true);
}

static bool	save_converted_colour(char id, char *line, t_data *data, int *count)
{
	if (id == 'C')
	{
		if (save_colour_rgb(line, &data->c, count))
		{
			data->ceiling = convert_rgb(data->c[0], data->c[1], data->c[2]);
			return (true);
		}
		return (false);
	}
	if (id == 'F')
	{
		if (save_colour_rgb(line, &data->f, count))
		{
			data->floor = convert_rgb(data->f[0], data->f[1], data->f[2]);
			return (true);
		}
		return (false);
	}
	return (false);
}

static bool	read_aux(int *count, char *line, t_data *data)
{
	if (!ft_strncmp("EH", line, 2))
		return (save_texture_path(line, &(data->game->hit_text_path), count));
	else if (!ft_strncmp("ES", line, 2))
		return (save_texture_path(line, &(data->game->shooting_text_path), count));
	else if (!ft_strncmp("EI", line, 2))
		return (save_texture_path(line, &(data->game->idle_text_path), count));
	else if (!ft_strncmp("IT", line, 2))
		return (save_texture_path(line, &(data->game->item_text_path), count));
	else if (!ft_strncmp("HE", line, 2))
		return (save_texture_path(line, &(data->game->health_text_path), count));
	return (false);
}

bool	read_textures_n_colours(int *count, char *line, t_data *data)
{
	while (ft_isspace(*line))
		line++;
	if (*line == '\n' || *line == '\0')
		return (true);
	if (!ft_strncmp("NO", line, 2))
		return (save_texture_path(line, &(data->direction[NORTH]), count));
	else if (!ft_strncmp("SO", line, 2))
		return (save_texture_path(line, &(data->direction[SOUTH]), count));
	else if (!ft_strncmp("EA", line, 2))
		return (save_texture_path(line, &(data->direction[EAST]), count));
	else if (!ft_strncmp("WE", line, 2))
		return (save_texture_path(line, &(data->direction[WEST]), count));
	else if (!ft_strncmp("C", line, 1))
		return (save_converted_colour('C', line, data, count));
	else if (!ft_strncmp("F", line, 1))
		return (save_converted_colour('F', line, data, count));
	return (read_aux(count, line, data));
	printf(BPINK "Error: invalid texture/colour info\n" RST);
	return (false);
}
