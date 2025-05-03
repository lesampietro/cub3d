#include "../../includes/cub3d.h"

void	is_empty(char *line)
{
	while (line && ft_isspace(*line))
	line++;
	if (!line)
	{
		printf(BPINK"Error: file is empty\n"RST);
		exit(EXIT_FAILURE);
	}
}

int	save_texture_path(char *line, char **path)
{
	line = check_line_info(line);
	if (!line)
	{
		printf(BPINK "Error: invalid texture/colour info\n" RST);
		free(line);
		exit(EXIT_FAILURE);
	}
	if (ft_strncmp("./", line, 2) != 0)
	{
		printf(BPINK "Error: invalid texture path\n" RST);
		free(line);
		exit(EXIT_FAILURE);
	}
	else
		*path = strdup(line);
	free(line);
	return (1);
}

int	save_colour_path(char *line, int *color_ptr)
{
	char	**split;
	line = check_line_info(line);
	if (!line)
	{
		printf(BPINK "Error: invalid texture/colour info\n" RST);
		free(line);
		exit(EXIT_FAILURE);
	}
	check_color(line);
	split = ft_split(line, ',');
	color_ptr = malloc(sizeof(int) * 3);
	if (!color_ptr)
	{
		printf(BPINK "Error: memory allocation failed\n" RST);
		free(line);
		exit(EXIT_FAILURE);
	}
	color_ptr[0] = ft_atoi(split[0]);
	color_ptr[1] = ft_atoi(split[1]);
	color_ptr[2] = ft_atoi(split[2]);
	free(line);
	return (1);
}

int	read_textures_n_colours(int count, char *line, t_data *data)
{
	if (!ft_strncmp("NO", line, 2))
		count += save_texture_path(line, &(data->direction[NORTH]));
	else if (!ft_strncmp("SO", line, 2))
		count += save_texture_path(line, &(data->direction[SOUTH]));
	else if (!ft_strncmp("EA", line, 2))
		count += save_texture_path(line, &(data->direction[EAST]));
	else if (!ft_strncmp("WE", line, 2))
		count += save_texture_path(line, &(data->direction[WEST]));
	else if (!ft_strncmp("C", line, 1))
		count += save_colour_path(line, data->c);
	else if (!ft_strncmp("F", line, 1))
		count += save_colour_path(line, data->f);
	return (count);
}

void	check_map_metadata(char *map_file, t_data *data)
{
	int		fd;
	char	*line;
	int		count;
	
	fd = safe_open(map_file);
	line = NULL;
	line = get_next_line(fd);
	is_empty(line);
	while (line)
	{
		while (ft_isspace(*line))
		line++;
		count = read_textures_n_colours(count, line, data);
		line = get_next_line(fd);
		if (count == 6 && (data->direction[NORTH] && data->direction[SOUTH] && data->direction[WEST] && data->direction[EAST] \
			&& data->c && data->f ))
			break ;
	}
	check_invalid_count(count);
}
