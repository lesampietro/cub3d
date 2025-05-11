#include "../../includes/cub3d.h"

void	find_map_first_line(int fd, char **map_line)
{
	size_t	i;

	while (*map_line)
	{
		i = 0;
		if (ft_strchr(*map_line, '1') || ft_strchr(*map_line, '0'))
		{
			while ((*map_line)[i])
			{
				if ((*map_line)[i] != '1' && !ft_isspace((*map_line)[i]) \
				&& (*map_line)[i] != '\n' && (*map_line)[i] != '0')
					break ;
				i++;
			}
			if ((*map_line)[i] == '\0' || (*map_line)[i] == '\n')
				return ;
		}
		free(*map_line);
		*map_line = get_next_line(fd);
	}
}

int	is_line_empty_or_spaces(char *line)
{
	while (*line)
	{
		if (!ft_isspace((unsigned char)*line))
			return (0);
		line++;
	}
	return (1);
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
			break ;
	}
	data->lin = i;
}

void	fill_with_spaces(char *map_line, char *tmp, int col)
{
	int		i;

	ft_strlcpy(map_line, tmp, col + 1);
	i = ft_strlen(tmp);
	while (i < col)
	{
		map_line[i] = ' ';
		i++;
	}
	map_line[i] = '\0';
}

void	get_map(t_data *data, char **map_line)
{
	int		i;
	char	*tmp;

	i = 0;
	*map_line = get_next_line(data->fd);
	find_map_first_line(data->fd, map_line);
	safe_malloc(data, (void **)&data->map, \
							sizeof(char *) * (data->lin + 1));
	while (*map_line && i < data->lin)
	{
		tmp = ft_strtrim(*map_line, "\n");
		safe_malloc(data, (void **)&data->map[i], \
							sizeof(char) * (data->col + 1));
		fill_with_spaces(data->map[i], tmp, data->col);
		free(tmp);
		free(*map_line);
		*map_line = get_next_line(data->fd);
		i++;
	}
	trim_empty_lines_at_end(data, i);
	data->map[i] = NULL;
}
