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

void	count_map_size(t_data *data, char **map_line)
{
	int			max_col;
	size_t		i;

	max_col = 0;
	*map_line = get_next_line(data->fd);
	find_map_first_line(data->fd, map_line);
	while (*map_line && **map_line != '\0')
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
		*map_line = get_next_line(data->fd);
		data->lin++;
	}
	data->col = max_col;
	close(data->fd);
}

void	validate_map(t_data *data)
{
	check_map_info(data);
	is_surrounded_by_walls(data, data->map, data->lin);
	check_map_elements(data, data->map);
}

void	process_map(int argc, char **argv, t_data *data)
{
	char	*map_line;
	
	map_line = NULL;
	check_args(argc);
	is_valid_ext(argv[1]);
	data->fd = safe_open(data, argv[1]);
	check_map_metadata(data, &map_line);
	data->fd = safe_open(data, argv[1]);
	count_map_size(data, &map_line);
	data->fd = safe_open(data, argv[1]);
	get_map(data, &map_line);
	validate_map(data);
	data->game->total_items = count_items(data);
	close(data->fd);
	free(map_line);
}
