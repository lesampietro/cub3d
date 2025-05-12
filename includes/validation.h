/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcaldas- <fcaldas-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:12:07 by fcaldas-          #+#    #+#             */
/*   Updated: 2025/05/12 18:12:08 by fcaldas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "cub3d.h"

void		process_map(int argc, char **argv, t_data *data);
int			count_elements(t_data *data);
int			safe_open(t_data *data, char *filename);
void		safe_malloc(t_data *data, void **to_malloc, int size);
void		check_map_metadata(t_data *data, char **map_line);
char		*check_line_info(char *line);
bool		check_color(char *line);
void		find_map_first_line(int fd, char **map_line);
void		check_map_info(t_data *data);
void		check_map_elements(t_data *data, char **map);
int			is_valid_char(char c);
bool		is_empty_line_in_map(char **line, int i);
void		is_surrounded_by_walls(t_data *data, char **map);
void		count_map_size(t_data *data, char **map_line);
int			count_items(t_data *data);
void		get_map(t_data *data, char **map_line);
void		process_info(t_data *data);
bool		read_textures_n_colours(int *count, char *line, t_data *data);
bool		validate_colour_info(char *line, char **colour);
void		allocate_colour(int **color_ptr, char **split);

#endif