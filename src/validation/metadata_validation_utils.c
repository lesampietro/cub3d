#include "../../includes/cub3d.h"

char	*check_line_info(char *line)
{
	char	**split;
	char	*path;
	// char	*tmp;

	split = NULL;
	// tmp = ft_strtrim(line, " \n");
	// split = ft_split(tmp, ' ');
	// free(tmp);
	path = NULL;
	split = ft_split(line, ' ');
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

void	check_color(t_data *data, char *line)
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
		free_and_exit(data->game, 1);
	}
	ft_free_split(split);
}

void	check_invalid_count(int count, t_data *data)
{
	if (count != 6)
	{
		printf(BPINK"Error: missing or duplicated texture/colour info"RST);
		free_and_exit(data->game, 1);
	}
}
