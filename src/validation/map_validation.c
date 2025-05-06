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

void	check_args(int argc)
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

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' \
		|| c == 'S' || c == 'N' || c == 'E' || c == 'W');
}

void	find_map_first_line(int fd, char **map_line)
{
	size_t i;
	
	while (*map_line)
	{
		i = 0;
		if (ft_strchr(*map_line, '1'))
		{
			while ((*map_line)[i])
			{
				if ((*map_line)[i] != '1' && !ft_isspace((*map_line)[i]) && (*map_line)[i] != '\n')
				break;
				i++;
			}
			if ((*map_line)[i] == '\0' || (*map_line)[i] == '\n')
			return;
		}
		free(*map_line);
		*map_line = get_next_line(fd);
	}
	printf(BPINK "Error: map not found\n" RST);
	exit(EXIT_FAILURE);
}

void	count_map_size(int fd, t_data *data, char **map_line)
{
	int			max_col;
	size_t		i;

	max_col = 0;
	*map_line = get_next_line(fd);
	find_map_first_line(fd, map_line);
	while (*map_line && **map_line != '\0' && **map_line != '\n')
	{
		i = 0;
		while (is_valid_char((*map_line)[i]) || ft_isspace((*map_line)[i]))
			i++;
		if (i == ft_strlen(*map_line) && (*map_line)[i - 1] == '\n')
		{
			data->col = i;
			if (data->col > max_col)
				max_col = data->col;
		}
		free(*map_line);
		*map_line = get_next_line(fd);
		data->lin++;
	}
	data->col = max_col;
	close(fd);
}

void	safe_malloc(void **data, int size)
{
	*data = malloc(size);
	if (!*data)
	{
		printf("Error: memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
}

void	get_map(int fd, t_data *data, char **map_line)
{
	int		i;

	i = 0;
	*map_line = get_next_line(fd);
	find_map_first_line(fd, map_line);
	safe_malloc((void**)&data->map, \
							sizeof(char *) * (data->lin + 1));
	while (*map_line && i < data->lin)
	{
		safe_malloc((void**)&data->map[i], \
									sizeof(char) * (data->col + 1));
		data->map[i] = ft_strtrim(*map_line, "\n");
		free(*map_line);
		*map_line = get_next_line(fd);
		i++;
	}
	data->map[i] = NULL;
}

void	check_map_info(char **map)
{
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid_char(map[i][j]))
			{
				printf(BPINK"Error: invalid character in map\n"RST);
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}

void	is_map_border(char **map, int lin, int i, int j)
{
	if (i == 0 || i == lin - 1 || j == 0 || j == (int)ft_strlen(map[i]))
	{
		printf(BPINK "Error: map is not surrounded by walls\n" RST);
		exit(EXIT_FAILURE);
	}
}

void	is_surrounded_by_walls(char **map, int lin)
{
	int		i;
	int		j;
	
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				is_map_border(map, lin, i, j);
				if (ft_isspace(map[i - 1][j]) || ft_isspace(map[i + 1][j]) \
					|| ft_isspace(map[i][j - 1]) || ft_isspace(map[i][j + 1]))
				{
					printf(BPINK"Error: map is not surrounded by walls\n"RST);
					exit(EXIT_FAILURE);
				}
			}
			j++;
		}
		i ++;
	}
}

void	validate_map(t_data *data)
{
	check_map_info(data->map);
	is_surrounded_by_walls(data->map, data->lin);
	// check_map_elements - checar sem tem pelo menos 1 elemento de player, mas 
}


void	process_map(int argc, char **argv, t_data *data)
{
	int		fd;
	char	*map_line;
	
	map_line = NULL;
	check_args(argc);
	is_valid_ext(argv[1]);
	fd = safe_open(argv[1]);
	check_map_metadata(fd, data, &map_line);
	fd = safe_open(argv[1]);
	count_map_size(fd, data, &map_line);
	fd = safe_open(argv[1]);
	get_map(fd, data, &map_line);
	// PRINT DEBUG
	int i = 0;
	printf("Map size: %d x %d\n", data->lin, data->col);
	while (data->map[i])
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	validate_map(data);
	close(fd);
	free(map_line);
}
