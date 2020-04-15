/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:50:28 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/16 15:15:59 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int			is_texture(char *line)
{
	return (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "S", 1) || !ft_strncmp(line, "EA", 2)
			|| !ft_strncmp(line, "WE", 2));
}

int			ft_clean_map(char **map, int nbr_line)
{
	int i;

	i = 0;
	while (i < nbr_line && !ft_strncmp(*(map++), "", 1))
	{
		free(*map);
		i++;
	}
	return (i);
}

int			check_char_map(char c)
{
	if (c != '0' && c != '1' && c != '2' && c != 'N' && c != 'S' && c != 'W'
		&& c != 'E' && c != ' ')
		return (1);
	return (0);
}

void	ft_swap(int *color)
{
	int		tmp;

	tmp = color[0];
	color[0] = color[2];
	color[2] = tmp;
}