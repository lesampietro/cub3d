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

int safe_open(char *filename)
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

int	save_texture_path(char *identifier, char *tmp, char **path)
{
	while (tmp && ft_isspace(*tmp))
	tmp++;
	if (!ft_strncmp(identifier, tmp, 2))
		tmp += 2;
	while (tmp && ft_isspace(*tmp))
		tmp++;
	if (tmp)
		*path = strdup(tmp);
	printf("Path for %s texture: %s", identifier, *path); // --> DEBUG
	return (1);
}

// int	convert_n_save_colours(char *identifier, char *tmp, uint32_t *colour)
void	check_duplicate_textures(t_data *data)
{
	if (data->no && data->so && data->ea && data->we && data->c && data->f)
	{
		if (num > 6)
		{
			printf(BPINK"Error: duplicate texture or colour identifier\n"RST);
			exit(EXIT_FAILURE);
		}
	}
}

	void	read_textures_n_colours(char *tmp, t_data *data)
{
	int		num;
	if (!ft_strncmp("NO", tmp, 2))
		num += save_texture_path("NO", tmp, &(data->no));
	else if (!ft_strncmp("SO", tmp, 2))
		num += save_texture_path("SO", tmp, &(data->so));
	else if (!ft_strncmp("EA", tmp, 2))
		num += save_texture_path("EA", tmp, &(data->ea));
	else if (!ft_strncmp("WE", tmp, 2))
		num += save_texture_path("WE", tmp, &(data->we));
	else if (!ft_strncmp("C", tmp, 1))
		num += save_texture_path("C", tmp, &(data->c));
	else if (!ft_strncmp("F", tmp, 1))
		num += save_texture_path("F", tmp, &(data->f));
}
	
void	check_map_metadata(char *map_file, t_data *data)
{
	int		fd;
	char	*tmp;
	
	tmp = NULL;
	fd = safe_open(map_file);
	tmp = get_next_line(fd);
	if (!tmp || tmp[0] == '\n' || tmp[0] == '\0')
	{
		printf(BPINK"Error: file is empty\n"RST);
		exit(EXIT_FAILURE);
	}
	while (tmp)
	{
		while (ft_isspace(*tmp))
		tmp++;
		read_textures_n_colours(tmp, data);
		// printf("%s", tmp);
		tmp = get_next_line(fd);
	}
}

void	validate_map(int argc, char **argv, t_data *data)
{
	char	**map;

	map = NULL;
	check_args(argc, argv);
	is_valid_ext(argv[1]);
	check_map_metadata(argv[1], data);
}