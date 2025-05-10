#include "../../includes/cub3d.h"

void	is_empty(char *line)
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

bool	save_texture_path(char *line, char **path, int *count)
{
	char	*tmp;
	tmp = check_line_info(line);
	if (!tmp)
	{
		printf(BPINK "Error: invalid texture/colour info\n" RST);
		free(tmp);
		return (false);
	}
	if (ft_strncmp("./", tmp, 2) != 0)
	{
		printf(BPINK "Error: invalid texture path\n" RST);
		free(tmp);
		return (false);
	}
	printf(BRED "path:%s\n" RST, tmp);
	*path = strdup(tmp);
	(*count)++;
	free(tmp);
	return (true);
}

bool	save_colour_path(char *line, int **color_ptr, int *count)
{
	char	**split;
	char	*colour;
	colour = check_line_info(line);
	if (!colour)
		return (false);
	if (!check_color(colour))
	{
		free(colour);
		return (false);
	}
	split = ft_split(colour, ',');
	*color_ptr = malloc(sizeof(int) * 3);
	if (!*color_ptr)
	{
		printf(BPINK "Error: memory allocation failed\n" RST);
		return (false);
	}
	(*color_ptr)[0] = ft_atoi(split[0]);
	(*color_ptr)[1] = ft_atoi(split[1]);
	(*color_ptr)[2] = ft_atoi(split[2]);
	ft_free_split(split);
	free(colour);
	// free(line);
	(*count)++;
	return (true);
}

bool	read_textures_n_colours(int *count, char *line, t_data *data)
{
	while (ft_isspace(*line))
		line++;
	// printf("line:%s\n", line);
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
		return (save_colour_path(line, &data->c, count));
	else if (!ft_strncmp("F", line, 1))
		return (save_colour_path(line, &data->f, count));
	return (false);
}

void	check_map_metadata(t_data *data, char **map_line)
{
	int		count;

	count = 0;
	*map_line = get_next_line(data->fd);
	is_empty(*map_line);
	while (*map_line)
	{
		if (!read_textures_n_colours(&count, *map_line, data))
		{
			free(*map_line);
			*map_line = NULL;
			free_and_exit(data->game, EXIT_FAILURE);
		}
		if (count == 6 && (data->direction[NORTH] && data->direction[SOUTH] \
			&& data->direction[WEST] && data->direction[EAST] \
			&& data->c && data->f ))
				break ;
		free(*map_line);
		*map_line = get_next_line(data->fd);
	}
	data->ceiling = convert_rgb(data->c[0], data->c[1], data->c[2]);
	data->floor = convert_rgb(data->f[0], data->f[1], data->f[2]);
	check_invalid_count(count);
	if (*map_line)
	{
		free(*map_line);
		*map_line = NULL;
	}
	close(data->fd);
}
