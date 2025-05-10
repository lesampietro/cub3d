#include "../../includes/cub3d.h"

char	*check_line_info(char *line)
{
	char	**split;
	char	*path;
	char	*tmp;

	split = NULL;
	tmp = ft_strtrim(line, " \n");
	split = ft_split(tmp, ' ');
	free(tmp);
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

bool	check_color(char *line)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	split = ft_split(line, ',');
	while (split[i])
	{
		j = 0;
		while (split[i][j])
		{
			if (!ft_isdigit(split[i][j]))
			{
				printf(BPINK "Error: invalid colour info\n" RST);
				ft_free_split(split);
				return (false);
			}
			j++;
		}
		i++;
	}
	if (i != 3 || split[3])
	{
		printf(BPINK "Error: invalid colour info\n" RST);
		ft_free_split(split);
		return (false);
	}
	ft_free_split(split);
	return (true);
}

void	check_invalid_count(t_data *data, int count, char *line)
{
	if (count == 6)
	{
		if (data->direction[NORTH] && data->direction[SOUTH] \
			&& data->direction[EAST] && data->direction[WEST] \
			&& data->f && data->c)
			return ;
	}
	printf(BPINK"Error: missing or duplicated texture/colour info"RST);
	free(line);
	line = NULL;
	free_and_exit(data->game, 1);
}
