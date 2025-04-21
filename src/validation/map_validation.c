#include "../../includes/cub3d.h"

int	is_valid_ext(char *file_ext)
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
        return (0);
    return (1);
}

void    validate_map(char   **argv)
{
    if (is_valid_ext(argv[1]))
        printf("Map extension is invalid");
        return ;
}