#include "../../includes/cub3d.h"

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
	if (!*path)
		*path = strdup(tmp);
	else
	{
		printf(BPINK "Error: more than 4 textures\n" RST);
		free(tmp);
		return (false);
	}
	(*count)++;
	free(tmp);
	return (true);
}

bool	save_colour_path(char *line, int **color_ptr, int *count)
{
	char	**split;
	char	*colour;
	static int	count_colours;

	colour = check_line_info(line);
	if (!colour)
		return (false);
	if (!check_color(colour))
	{
		free(colour);
		return (false);
	}
	if (count_colours > 1)
	{
		printf(BPINK "Error: more than 2 colours\n" RST);
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
	count_colours++;
	(*count)++;
	return (true);
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
		return (save_colour_path(line, &data->c, count));
	else if (!ft_strncmp("F", line, 1))
		return (save_colour_path(line, &data->f, count));
	printf(BPINK "Error: invalid texture/colour info\n" RST);
	return (false);
}

bool	is_map_line(char *line)
{
	int	i;
	bool	map;

	i = 0;
	map = false;
	if (ft_strchr(line, '1'))
	{
		while (ft_isspace(line[i]))
			i++;
		while (line[i] && line[i] != '\n')
		{
			if (line[i] == '1' || line[i] == '0' || ft_isspace(line[i]))
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
		{
			break ;
		}
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
	data->ceiling = convert_rgb(data->c[0], data->c[1], data->c[2]);
	data->floor = convert_rgb(data->f[0], data->f[1], data->f[2]);
	if (*map_line)
	{
		free(*map_line);
		*map_line = NULL;
	}
	close(data->fd);
}
