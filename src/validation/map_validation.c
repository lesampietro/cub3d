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
		|| c == 'S' || c == 'N' || c == 'E' || c == 'W'
		|| c == 'H' || c == 'I' || c == 'E');
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
	// printf("Map size: %d x %d\n", data->lin, data->col);
	close(fd);
}

void	init_enemies(t_game *game, int e)
{	
	game->enemy_count++;
	game->element[e].type = ENEMY;
	game->element[e].idle_texture_path = "./assets/enemies/wizard idle.png";
	game->element[e].visible = false;
	game->element[e].shooting_texture_path = "./assets/enemies/wizard attack2.png";
	game->element[e].first_visible_time = 0;
	printf("Enemy %d: %d at (%f, %f)\n", e, game->element[e].type, \
		game->element[e].x, game->element[e].y);
	
}

void	init_element_type(char c, t_game *game, int e)
{
	game->element[e].alive = true;
	game->element[e].health = 100;

	if (c == 'X')
		init_enemies(game, e);
	else if (c == 'I')
	{
		game->element[e].type = ITEM;
	}
	else if (c == 'H')
	{

		game->element[e].type = HEALTH;
	}
}

void	get_element_pos(char *map_line, t_data *data, int i)
{
	int		j;
	int		e;
	e = data->game->element_count;
	j = 0;
	while (map_line[j])
	{
		if (map_line[j] == 'X' || map_line[j] == 'I' || \
			map_line[j] == 'H')
			{
				data->game->element[e].x = j + 0.5;
				data->game->element[e].y = i + 0.5;
				printf("Element %d: %c at (%f, %f)\n", e, map_line[j], \
					data->game->element[e].x, data->game->element[e].y);
				init_element_type(map_line[j], data->game, e);
				e++;
			}
			j++;
	}
	if (e > 15)
	{
		printf(BPINK "Error: too many elements. Maximum of 15\n" RST);
		exit(EXIT_FAILURE);
	}
	data->game->element_count = e;
}

void	get_player_pos(char *map_line, t_data *data, int i)
{
	int		j;

	j = 0;
	while (map_line[j])
	{
		if (map_line[j] == 'N' || map_line[j] == 'S' || \
			map_line[j] == 'E' || map_line[j] == 'W')
		{
			data->pov = map_line[j];
			data->game->player_pos.x = j + 0.5;
			data->game->player_pos.y = i + 0.5;
			return ;
		}
		j++;
	}
}

void	get_positions(char *map_line, t_data *data, int i)
{
	get_player_pos(map_line, data, i);
	get_element_pos(map_line, data, i);
}

void	get_map(int fd, t_data *data, char **map_line)
{
	int		i;
	// int		j;

	i = 0;
	*map_line = get_next_line(fd);
	find_map_first_line(fd, map_line);
	data->map = malloc(sizeof(char *) * (data->lin + 1));
	//PROTECT MALLOC (SUBSTITUIR MALLOC POR SAFE_MALLOC - ECONOMIA DE LINHAS)
	while (*map_line && i < data->lin)
	{
		// j = 0;
		data->map[i] = malloc(sizeof(char) * (data->col + 1));
		// PROTECT MALLOC (SUBSTITUIR MALLOC POR SAFE_MALLOC - ECONOMIA DE LINHAS)
		data->map[i] = ft_strtrim(*map_line, "\n");
		get_positions(data->map[i], data, i);
		free(*map_line);
		*map_line = get_next_line(fd);
		i++;
	}
	data->map[i] = NULL;
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
	count_map_size(fd, data, &map_line);
	fd = safe_open(argv[1]);
	get_map(fd, data, &map_line);
	// PRINT DEBUG
	// int i = 0;
	// printf("Map size: %d x %d\n", data->lin, data->col);
	// while (data->map[i])
	// {
	// 	printf("%s\n", data->map[i]);
	// 	i++;
	// }
	// check_map(data->map, data); //TO BE DONE
	close(fd);
	free(map_line);
}