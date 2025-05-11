#include "../../includes/cub3d.h"

void	is_empty_file(char *line)
{
	while (line && ft_isspace(*line))
		line++;
	if (!line)
	{
		printf(BPINK"Error: file is empty\n"RST);
		free(line);
		line = NULL;
		exit(EXIT_FAILURE);
	}
}

void	safe_malloc(t_data *data, void **to_malloc, int size)
{
	*to_malloc = malloc(size);
	if (!*to_malloc)
	{
		printf("Error: memory allocation failed\n");
		free_and_exit(data->game, EXIT_FAILURE);
	}
}

int	safe_open(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf(BPINK"Error: failed to open file\n"RST);
		free_and_exit(data->game, EXIT_FAILURE);
	}
	return (fd);
}

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == ' ' \
		|| c == 'S' || c == 'N' || c == 'E' || c == 'W'
		|| c == 'X' || c == 'I' || c == 'H' );
}

bool	is_empty_line_in_map(char **line, int i)
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
				return (true);
			i++;
		}
	}
	return (false);
}
