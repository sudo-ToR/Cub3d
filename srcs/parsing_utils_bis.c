/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:36:39 by user42            #+#    #+#             */
/*   Updated: 2020/12/28 16:40:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/parsing.h"

int			ft_isnum(char *line)
{
	return (!ft_strncmp(line, "R", 1) || !ft_strncmp(line, "F", 1)
		|| !ft_strncmp(line, "C", 1));
}

void		ft_pars_utils_map(int ret, char *line, t_pars *p)
{
	if (ret == 0 && ft_isdigit(line[0]))
		ft_realloc(&p->height, &p->map, line);
	p->map += ft_clean_map(p->map, p->height);
}

int			ft_pars_num(char *line, t_pars *p)
{
	if (!ft_strncmp(line, "R ", 2) && !p->map)
	{
		if (clean_num(line, 0, &p->r))
			return (DUPLICATION_ARGUMENT);
	}
	else if (!ft_strncmp(line, "F ", 2) && !p->map)
	{
		if (clean_num(line, 1, &p->f))
			return (DUPLICATION_ARGUMENT);
	}
	else if (!ft_strncmp(line, "C ", 2) && !p->map)
	{
		if (clean_num(line, 1, &p->c))
			return (DUPLICATION_ARGUMENT);
	}
	return (0);
}