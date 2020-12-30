/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 12:42:55 by user42            #+#    #+#             */
/*   Updated: 2020/12/30 17:09:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			count_arg(char *line, int id)
{
	int i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		while (line[i] && !ft_isdigit(line[i]))
			i++;
		if (line[i] && ft_isdigit(line[i]))
			count++;
		while (line[i] && ft_isdigit(line[i]))
			i++;
	}
	if ((id == 0 && count == 2) || (id == 1 && count == 3))
		return (0);
	return (1);
}

int			check_clean_num(int **res, int id, char *line)
{
	if (*res != NULL)
		return (1);
	if (count_arg(line, id))
	{
		free(line);
		return (2);
	}
	return (0);
}

int			is_map(char *line)
{
	int i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && ft_isdigit(line[i]))
		return (1);
	return (0);
}

void		wrong_arg(char *line, t_mlx *m)
{
	free(line);
	aff_error(WRONG_ARG, m);
}

void		clean_num_moulinette(char **texture)
{
	free(texture);
	*texture = NULL;
}
