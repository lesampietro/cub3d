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

static bool	save_colour_rgb(char *line, int **colour_ptr, int *count)
{
	char		**split;
	char		*colour;
	static int	count_colours;

	colour = NULL;
	if (!validate_colour_info(line, &colour))
		return (false);
	if (count_colours > 1)
	{
		printf(BPINK "Error: duplicated colour info\n" RST);
		free(colour);
		return (false);
	}
	split = ft_split(colour, ',');
	allocate_colour(colour_ptr, split);
	ft_free_split(split);
	free(colour);
	count_colours++;
	(*count)++;
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
	printf(BPINK "Error: invalid texture/colour info\n" RST);
	return (false);
}
