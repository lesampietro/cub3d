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

// int		count_map_size(char *filename)
// {
// 	int		fd;
// 	int		count;
// 	char	*line;

// 	fd = safe_open(filename);
// 	count = 0;
// 	while (get_next_line(fd) > 0)
// 	{
// 		count++;
// 		free(line);
// 	}
// 	close(fd);
// 	return (count);
// }

// char	**get_map(char *filename)
// {
// 	int		fd;
// 	char	*line;
// 	char	**map;

// 	fd = safe_open(filename);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		if (ft_strchr(line, '1'))
// 			break ;
// 		break ;
// 		line = get_next_line(fd);
// 	}
// 	return (map);
// }



void	validate_map(int argc, char **argv, t_data *data)
{
	char	*map_line;

	map_line = NULL;
	check_args(argc);
	is_valid_ext(argv[1]);
	check_map_metadata(argv[1], data, map_line);
	// data->map = get_map(argv[1]);
	// //printf("Map size: %d\n", count_map_size(argv[1]));
	// while(data->map[data->lin])
	// {
	// 	printf("Map: %s\n", data->map[data->lin]);
	// 	data->lin++;
	// }
	//printf("Map: %s\n", data->map[0]);
	// check_map(data->map, data);
}