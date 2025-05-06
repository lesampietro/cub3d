#include "../../includes/cub3d.h"

void	check_path_ext(char *path_ext)
{
	char	*valid_ext;
	int		i;
	int		len;

	i = 0;
	valid_ext = ".png";
	len = ft_strlen(path_ext);
	len = len - 4;
	while (path_ext[len] && valid_ext[i] && path_ext[len] == valid_ext[i])
	{
		i++;
		len++;
	}
	if (valid_ext[i] == '\0' && path_ext[len] == '\0')
		return ;
	printf(BPINK"Texture extension is invalid\n"RST);
	exit(EXIT_FAILURE);
}