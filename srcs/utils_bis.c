/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 12:42:55 by user42            #+#    #+#             */
/*   Updated: 2020/12/30 12:54:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			count_arg(char *line, int id)
{
	int i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
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
		return (2);
	return (0);
}
