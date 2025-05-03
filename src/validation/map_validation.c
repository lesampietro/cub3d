#include "../../includes/cub3d.h"

void	is_valid_ext(char *file_ext)
{
	char	*valid_ext;
	int		i;
	int		len;

	i = 0;
	valid_ext = ".cub";
	len = ft_strlen(file_ext);
	len = len - 4;
	while (file_ext[len] && valid_ext[i] && file_ext[len] == valid_ext[i])
	{
		i++;
		len++;
	}
	if (valid_ext[i] == '\0' && file_ext[len] == '\0')
		return ;
	printf(BPINK"Map extension is invalid\n"RST);
	exit(EXIT_FAILURE);
}

void	check_args(int argc, char **argv)
{
	if (argc < 2)
	{
		printf(BPINK"Too few arguments: please provide a path to a map\n"RST);
		exit(EXIT_FAILURE);
	}
	else if (argc > 2)
	{
		printf(BPINK"Too many arguments\n"RST);
		exit(EXIT_FAILURE);
	}
	else
		return ;
}

int	safe_open(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf(BPINK"Error: failed to open file\n"RST);
		//funçao para lidar com erro - dar free e sair
		exit(EXIT_FAILURE);
	}
	return (fd);
}

char	*check_line_info(char *line)
{
	char	**split;
	char	*path;

	split = NULL;
	line = ft_strtrim(line, " \n");
	split = ft_split(line, ' ');
	path = NULL;
	if (split[2])
	{
		printf(BPINK "Error: too much texture info\n" RST);
		ft_free_split(split);
		return (NULL);
	}
	if (split[1])
	{
		path = ft_strdup(split[1]);
		ft_free_split(split);
		return (path);
	}
	else
	{
		printf(BPINK "Error: missing texture info\n" RST);
		ft_free_split(split);
		return (NULL);
	}
}

void	check_color(char *line)
{
	int		i;
	int		j;
	char	**split;

	i = -1;
	j = 0;
	split = ft_split(line, ',');
	while (split[++i])
	{
		if (!ft_isdigit(split[i][j]))
		break ;
	}
	if (i != 3 || split[3])
	{
		printf(BPINK "Error: invalid colour info\n" RST);
		ft_free_split(split);
		exit(EXIT_FAILURE);
	}
	ft_free_split(split);
}

int	save_texture_path(char *identifier, char *line, char **path)
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

int	save_colour_path(char *identifier, char *line, char **path)
{
	line = check_line_info(line);
	if (!line)
	{
		printf(BPINK "Error: invalid texture/colour info\n" RST);
		free(line);
		exit(EXIT_FAILURE);
	}
	check_color(line);
	*path = strdup(line);
	free(line);
	return (1);
}


int	read_textures_n_colours(int count, char *line, t_data *data)
{
	if (!ft_strncmp("NO", line, 2))
		count += save_texture_path("NO", line, &(data->direction[NORTH]));
	else if (!ft_strncmp("SO", line, 2))
		count += save_texture_path("SO", line, &(data->direction[SOUTH]));
	else if (!ft_strncmp("EA", line, 2))
		count += save_texture_path("EA", line, &(data->direction[EAST]));
	else if (!ft_strncmp("WE", line, 2))
		count += save_texture_path("WE", line, &(data->direction[WEST]));
	else if (!ft_strncmp("C", line, 1))
		count += save_colour_path("C", line, &(data->c));
	else if (!ft_strncmp("F", line, 1))
		count += save_colour_path("F", line, &(data->f));
	return (count);
}

void	check_invalid_count(int count, t_data *data)
{
	if (count != 6)
	{
		printf(BPINK"Error: missing or duplicated texture/colour info"RST);
		exit(EXIT_FAILURE);
	}
}

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
			&& data->c && data->f))
			break ;
	}
	check_invalid_count(count, data);
}

void	validate_map(int argc, char **argv, t_data *data)
{
	char	**map;

	map = NULL;
	check_args(argc, argv);
	is_valid_ext(argv[1]);
	check_map_metadata(argv[1], data);
	// printf("Path for NO = %s", data->no);
	// printf("Path for SO = %s", data->so);
	// printf("Path for WE = %s", data->we);
	// printf("Path for EA = %s", data->ea);
	// printf("Path for C = %s", data->c);
	// printf("Path for F = %s", data->f);
}