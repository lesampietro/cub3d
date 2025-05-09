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

int	safe_open(char *filename, t_data *data)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf(BPINK"Error: failed to open file\n"RST);
		free_and_exit(data->game, 1);
	}
	return (fd);
}

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' \
		|| c == 'S' || c == 'N' || c == 'E' || c == 'W'
		|| c == 'X' || c == 'I' || c == 'H' );
}

void	find_map_first_line(int fd, char **map_line)
{
	size_t i;
	
	while (*map_line)
	{
		i = 0;
		if (ft_strchr(*map_line, '1') || ft_strchr(*map_line, '0'))
		{
			while ((*map_line)[i])
			{
				if ((*map_line)[i] != '1' && !ft_isspace((*map_line)[i]) \
				&& (*map_line)[i] != '\n' && (*map_line)[i] != '0')
					break;
				i++;
			}
			if ((*map_line)[i] == '\0' || (*map_line)[i] == '\n')
				return;
		}
		free(*map_line);
		*map_line = get_next_line(fd);
	}
}

void	count_map_size(t_data *data)
{
	int			max_col;
	size_t		i;

	i = 0;
	max_col = 0;
	data->map_line = get_next_line(data->fd);
	find_map_first_line(data->fd, &data->map_line);
	while (data->map_line && data->map_line[i] != '\0')
	{
		i = 0;
		while (is_valid_char(data->map_line[i]) || ft_isspace(data->map_line[i]))
			i++;
		if (i == ft_strlen(data->map_line) && data->map_line[i - 1] == '\n')
		{
			data->col = i;
			if (data->col > max_col)
				max_col = data->col;
		}
		free(data->map_line);
		data->map_line = get_next_line(data->fd);
		data->lin++;
	}
	data->col = max_col;
	close(data->fd);
}

void	safe_malloc(void **to_malloc, int size, t_data *data)
{
	*to_malloc = malloc(size);
	if (!*to_malloc)
	{
		printf("Error: memory allocation failed\n");
		free_and_exit(data->game, 1);
	}
}

int	is_line_empty_or_spaces(char *line)
{
	while (*line)
	{
		if (!ft_isspace((unsigned char)*line))
			return (0); // encontrou algo que não é espaço
		line++;
	}
	return (1); // só tinha espaços
}

void	trim_empty_lines_at_end(t_data *data, int i)
{
	while (i > 0)
	{
		if (!data->map[i - 1] || is_line_empty_or_spaces(data->map[i - 1]))
		{
			free(data->map[i - 1]);
			data->map[i - 1] = NULL;
			i--;
		}
		else
			break;
	}
	data->lin = i;
}

void	process_element(t_data *data, int x, int y, char c)
{
	t_game		*game = data->game;
	t_element	*e;

	if (game->element_count >= 34)
	{
		printf(BPINK"Error: too many elements in the map. Max = 35\n"RST);
		free_and_exit(data->game, 1);
	}

	e = &game->element[game->element_count];
	e->x = (float)x + 0.5f; // centraliza na célula
	e->y = (float)y + 0.5f;
	e->alive = true;
	e->visible = false;
	e->last_shot_time = 0;
	e->first_visible_time = 0;
	e->dist_rank = 0;
	e->distance = 0;
	e->id = game->element_count;
	e->got_hit = false;
	e->shooting = false;
	e->shooting_texture_path = NULL;
	e->hit_texture_path = NULL;
	e->texture_path = NULL;
	
	if (c == 'X')
	{
		e->type = ENEMY;
		e->health = 100;
		e->idle_texture_path = "./assets/enemies/wizard idle.png";
		e->shooting_texture_path = "./assets/enemies/wizard attack3.png";
		e->hit_texture_path = "./assets/enemies/wizard_strucky.png";
		e->texture_path = NULL;
		// e->got_hit = false;
		// e->shooting = false;
	}
	else if (c == 'I')
	{
		e->type = ITEM;
		e->health = 100;
		e->idle_texture_path = "./assets/items/resource.png";
		e->texture_path = NULL;
	}
	else if (c == 'H')
	{
		e->type = HEALTH;
		e->health = POTION_HEALTH;
		e->idle_texture_path = "./assets/items/red_potion.png";
		e->texture_path = NULL;
	}
	game->element_count++;
}


void	process_info(char *map_line, t_data *data, int map_index)
{
	int		x;
	char	c;

	x = 0;
	while (map_line[x] != '\0')
	{
		c = map_line[x];
		if (c == 'S' || c == 'N' || c == 'E' || c == 'W')
		{
			data->pov = c;
			data->game->player_pos.x = x + 0.5f; // centraliza na célula
			data->game->player_pos.y = map_index + 0.5f;
			map_line[x] = '0';
		}
		if (c == 'X' || c == 'I' || c == 'H')
			process_element(data, x, map_index, c);
		x++;
	}

}

void	get_map(t_data *data)
{
	int		i;

	i = 0;
	data->map_line = get_next_line(data->fd);
	find_map_first_line(data->fd, &data->map_line);
	safe_malloc((void**)&data->map, sizeof(char *) * (data->lin + 1), data);
	while (data->map_line && i < data->lin)
	{
		data->map[i] = ft_strtrim(data->map_line, "\n");
		free(data->map_line);
		process_info(data->map[i], data, i);
		data->map_line = get_next_line(data->fd);
		i++;
	}
	trim_empty_lines_at_end(data, i);
	data->map[i] = NULL;
	
}

void	is_empty_line(char **line, int i)
{
	int		c;

	c = 0;
	if (line[i][c] == '\0')
	{
		while (line[i])
		{
			c = 0;
			while (line[i][c] && ft_isspace(line[i][c]))
				c++;
			if (line[i][c] != '\0')
			{
				printf(BPINK"Error: empty line in map\n"RST);
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}

}

void	check_map_info(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		is_empty_line(data->map, i);
		while (data->map[i][j])
		{
			if (!is_valid_char(data->map[i][j]))
			{
				printf(BPINK"Error: invalid character in map\n"RST);
				free_and_exit(data->game, 1);
			}
			j++;
		}
		i++;
	}
}


int count_items(t_data *data)
{
	int i;
	int j;
	int count;

	count = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'I')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	is_map_border(char **map, int lin, int i, int j)
{
	if (i == 0 || i == lin - 1 || j == 0 || j == (int)ft_strlen(map[i]) - 1)
	{
		printf(BPINK "Error: map is not surrounded by walls\n" RST);
		exit(EXIT_FAILURE);
	}
	if (!map[i - 1][j] || !map[i + 1][j])
	{
			printf(BPINK "Error: map is not surrounded by walls\n" RST);
			exit(EXIT_FAILURE);
	}
}

void	is_surrounded_by_walls(char **map, int lin, t_data *data)
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
					free_and_exit(data->game, 1);
				}
			}
			j++;
		}
		i ++;
	}
}

void	validate_map(t_data *data)
{
	check_map_info(data);
	is_surrounded_by_walls(data->map, data->lin, data);
	// check_map_elements - checar sem tem pelo menos 1 elemento de player, mas 
}

void	process_map(int argc, char **argv, t_data *data)
{
	check_args(argc);
	is_valid_ext(argv[1]);
	data->fd = safe_open(argv[1], data);
	check_map_metadata(data);
	data->fd = safe_open(argv[1], data);
	count_map_size(data);
	data->fd = safe_open(argv[1], data);
	get_map(data);
	validate_map(data);
	data->game->total_items = count_items(data);
	close(data->fd);
	free(data->map_line);
}

// PRINT DEBUG
// int i = 0;
// printf("Map size: %d x %d\n", data->lin, data->col);
// while (data->map[i])
// {
// 	printf("%s\n", data->map[i]);
// 	i++;
// }