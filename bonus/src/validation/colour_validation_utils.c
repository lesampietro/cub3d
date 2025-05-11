/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_validation_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsampiet <lsampiet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 23:57:46 by lsampiet          #+#    #+#             */
/*   Updated: 2025/05/10 23:57:51 by lsampiet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_invalid_char_within_colour(char **split, int *i)
{
	int	j;

	while (split[*i])
	{
		j = 0;
		while (split[*i][j])
		{
			if (!ft_isdigit(split[*i][j]))
			{
				printf(BPINK "Error: invalid colour info\n" RST);
				ft_free_split(split);
				return (false);
			}
			j++;
		}
		(*i)++;
	}
	return (true);
}

bool	check_color(char *line)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(line, ',');
	is_invalid_char_within_colour(split, &i);
	if (i != 3 || split[3])
	{
		printf(BPINK "Error: invalid colour info\n" RST);
		ft_free_split(split);
		return (false);
	}
	ft_free_split(split);
	return (true);
}

bool	validate_colour_info(char *line, char **colour)
{
	*colour = check_line_info(line);
	if (!*colour)
		return (false);
	if (!check_color(*colour))
	{
		free(colour);
		return (false);
	}
	return (true);
}

void	allocate_colour(int **color_ptr, char **split)
{
	*color_ptr = malloc(sizeof(int) * 3);
	if (!*color_ptr)
	{
		printf(BPINK "Error: memory allocation failed\n" RST);
		exit(EXIT_FAILURE);
	}
	(*color_ptr)[0] = ft_atoi(split[0]);
	(*color_ptr)[1] = ft_atoi(split[1]);
	(*color_ptr)[2] = ft_atoi(split[2]);
}
