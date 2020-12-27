/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 17:50:28 by lnoirot           #+#    #+#             */
/*   Updated: 2020/12/16 11:30:29 by user42           ###   ########.fr       */
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

int			check_char_map(char **map, int nbr_line)
{
	int i;
	int j;
	int b;

	i = 0;
	b = 0;
	while (i < nbr_line)
	{
		j = 0;
		while (map[i][j])
		{
			if ((map[i][j] != '0' && map[i][j] != '1' && map[i][j] != '2'
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W'
					&& map[i][j] != 'E') || b > 1)
				return (1);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
				b += 1;
			j++;
		}
		i++;
	}
	if (b == 0)
		return (1);
	return (0);
}

void		ft_swap(int *color)
{
	int		tmp;

	tmp = color[0];
	color[0] = color[2];
	color[2] = tmp;
}
