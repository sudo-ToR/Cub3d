/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 16:25:18 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/25 10:47:52 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

int		cut_space(char ***map, int nbr_line)
{
	int i;
	int j;

	while (nbr_line > 0)
	{
		i = 0;
		j = 0;
		while ((*map)[nbr_line - 1][i])
		{
			if (i % 2 == 0 && (*map)[nbr_line - 1][i] != ' ')
				(*map)[nbr_line - 1][j++] = (*map)[nbr_line - 1][i];
			if (i % 2 != 0 && (*map)[nbr_line - 1][i] != ' ')
				return (1);
			i++;
		}
		(*map)[nbr_line - 1][j] = 0;
		nbr_line--;
	}
	return (0);
}

int		check_map_border(char **map, int nbr_line, int length)
{
	int i;

	i = 0;
	while (i < nbr_line - 1 && map[i][length - 1])
	{
		if (map[i][0] != '1' || map[i][length - 1] != '1')
			return (WRONG_MAP);
		i++;
	}
	i = 0;
	while (i < length)
	{
		if (map[0][i] != '1' || map[nbr_line - 1][i] != '1')
			return (WRONG_MAP);
		i += 2;
	}
	return (cut_space(&map, nbr_line));
}

int		check_map(char **map, int nbr_line, int length)
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
			if (check_char_map(map[i][j]))
				return (WRONG_MAP);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				b += 1;
			j++;
		}
		if (j != length)
			return (WRONG_MAP);
		i++;
	}
	if (b != 1 || check_map_border(map, nbr_line, length))
		return (WRONG_MAP);
	return (0);
}

int		ft_check_parsing(t_pars *p, int fd)
{
	if (p->r[0] > WIDTH_MAX)
		p->r[0] = WIDTH_MAX;
	if (p->r[1] > HEIGHT_MAX)
		p->r[1] = HEIGHT_MAX;
	if (fd == -1)
		return (aff_error(WRONG_PATH_CUB_FILE));
	else if (!p->no || !p->so || !p->ea || !p->s || !p->we)
		return (aff_error(WRONG_TEXTURE));
	else if (!p->r || p->r[0] <= 0 || p->r[1] <= 0)
		return (aff_error(WRONG_RESOLUTION));
	else if (!p->c || p->c[0] < 0 || p->c[1] < 0 || p->c[2] < 0)
		return (aff_error(WRONG_C));
	else if (!p->f || p->f[0] < 0 || p->f[1] < 0 || p->f[2] < 0)
		return (aff_error(WRONG_F));
	else if (!p->map || (check_map(p->map, p->height, ft_strlen(p->map[0]))))
		return (aff_error(WRONG_MAP));
	p->width = ft_strlen(p->map[0]);
	return (0);
}

int		aff_error(int error)
{
	ft_printf("Invalide cub file : ");
	if (error == WRONG_PATH_CUB_FILE)
		return (ft_printf("wrong path for cub file\n"));
	else if (error == WRONG_ARG)
		return (ft_printf("wrong argument in cub file\n"));
	else if (error == WRONG_TEXTURE)
		return (ft_printf("wrong texture in cub file\n"));
	else if (error == WRONG_RESOLUTION)
		return (ft_printf("incorrect resolution\n"));
	else if (error == WRONG_C)
		return (ft_printf("incorrect ceiling color\n"));
	else if (error == WRONG_F)
		return (ft_printf("incorrect floor color\n"));
	else if (error == WRONG_MAP)
		return (ft_printf("invalid map\n"));
	return (0);
}
