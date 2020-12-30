/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:36:39 by user42            #+#    #+#             */
/*   Updated: 2020/12/30 16:14:08 by user42           ###   ########.fr       */
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
	int ret;

	if (!ft_strncmp(line, "R ", 2) && !p->map)
	{
		if ((ret = clean_num(line, 0, &p->r) == 1))
			return (DUPLICATION_ARGUMENT);
		else if (ret == 2)
			return (WRONG_RESOLUTION);
	}
	else if (!ft_strncmp(line, "F ", 2) && !p->map)
	{
		if ((ret = clean_num(line, 1, &p->f) == 1))
			return (DUPLICATION_ARGUMENT);
		else if (ret == 2)
			return (WRONG_F);
	}
	else if (!ft_strncmp(line, "C ", 2) && !p->map)
	{
		if ((ret = clean_num(line, 1, &p->c) == 1))
			return (DUPLICATION_ARGUMENT);
		if (ret == 2)
			return (WRONG_C);
	}
	return (0);
}

void		cut_space(t_pars *p)
{
	int i;
	int j;

	i = -1;
	while (p->map[++i])
	{
		j = -1;
		while (p->map[i][++j])
		{
			if (ft_isspace(p->map[i][j]))
				p->map[i][j] = '1';
		}
	}
}

void		free_clean_num(char **stock, char *line)
{
	free_table(stock);
	free(line);
}
