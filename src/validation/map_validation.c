#include "../../includes/cub3d.h"

void    is_valid_ext(char *file_ext)
{
	char	*valid_ext;
    int     i;
    int     len;

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
    printf(BPINK"Map extension is invalid"RST);
    exit(EXIT_FAILURE);
}

void	check_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
    {
        printf(BPINK"Failure opening map"RST);
		exit(EXIT_FAILURE);
    }
	close(fd);
	return ;
}

void    check_args(int argc, char **argv)
{
    if (argc < 2)
	{
		printf(BPINK"Too few arguments: please provide a path to a map"RST);
		exit(EXIT_FAILURE);
	}
    else  if (argc > 2)
    {
        printf(BPINK"Too many arguments"RST);
        exit(EXIT_FAILURE);
    }
    else
        return ;
}

void    validate_map(int argc, char   **argv)
{
    char    **map;

    map = NULL;
    check_args(argc, argv);
    check_path(argv[1]);
    is_valid_ext(argv[1]); 
}