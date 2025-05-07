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

void	save_texture_path(char *line, char **path, int *count, t_data *data)
{
	line = check_line_info(line);
	if (!line)
	{
		printf(BPINK "Error: invalid texture/colour info\n" RST);
		free(line);
		free_and_exit(data->game);
	}
	if (ft_strncmp("./", line, 2) != 0)
	{
		printf(BPINK "Error: invalid texture path\n" RST);
		free(line);
		free_and_exit(data->game);
	}
	else
		*path = strdup(line);
	free(line);
	(*count)++;
}

void	save_colour_path(char *line, int **color_ptr, int *count, t_data *data)
{
	char	**split;
	line = check_line_info(line);
	if (!line)
	{
		printf(BPINK "Error: invalid texture/colour info\n" RST);
		free(line);
		free_and_exit(data->game);
	}
	check_color(line);
	split = ft_split(line, ',');
	*color_ptr = malloc(sizeof(int) * 3);
	if (!*color_ptr)
	{
		printf(BPINK "Error: memory allocation failed\n" RST);
		free(line);
		free_and_exit(data->game);
	}
	(*color_ptr)[0] = ft_atoi(split[0]);
	(*color_ptr)[1] = ft_atoi(split[1]);
	(*color_ptr)[2] = ft_atoi(split[2]);
	//
	ft_free_split(split);
	//
	free(line);
	(*count)++;
}

void	read_textures_n_colours(int *count, char *line, t_data *data)
{
	if (!ft_strncmp("NO", line, 2))
		save_texture_path(line, &(data->direction[NORTH]), count, data);
	else if (!ft_strncmp("SO", line, 2))
		save_texture_path(line, &(data->direction[SOUTH]), count, data);
	else if (!ft_strncmp("EA", line, 2))
		save_texture_path(line, &(data->direction[EAST]), count, data);
	else if (!ft_strncmp("WE", line, 2))
		save_texture_path(line, &(data->direction[WEST]), count, data);
	else if (!ft_strncmp("C", line, 1))
		save_colour_path(line, &data->c, count, data);
	else if (!ft_strncmp("F", line, 1))
		save_colour_path(line, &data->f, count, data);
}

void	check_map_metadata(int fd, t_data *data, char **map_line)
{
	int		count;

	count = 0;
	*map_line = get_next_line(fd);
	is_empty(*map_line);
	while (*map_line)
	{
		while (ft_isspace(**map_line))
			(*map_line)++;
		read_textures_n_colours(&count, *map_line, data);
		if (count == 6 && (data->direction[NORTH] && data->direction[SOUTH] \
			&& data->direction[WEST] && data->direction[EAST] \
			&& data->c && data->f ))
				break ;
		*map_line = get_next_line(fd);
	}
	data->ceiling = convert_rgb(data->c[0], data->c[1], data->c[2]);
	data->floor = convert_rgb(data->f[0], data->f[1], data->f[2]);
	check_invalid_count(count, data);
	close(fd);
}
