#include "../../includes/cub3d.h"

bool	is_invalid_ext(char *file_ext)
{
	char	*valid_ext;
	char	*ext;

	valid_ext = ".cub";
	ext = ft_strrchr(file_ext, '.');
	if (!ext)
        return (true);
	if ((ft_strlen(ext) != 4) || (ft_strncmp(ext, valid_ext, 4) != 0))
        return (true);
    return (false);
}

void    validate_map(char   **argv)
{
    if (is_invalid_ext(argv[1]));
        printf("Map extension is invalid");
}