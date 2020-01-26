/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:49:05 by lnoirot           #+#    #+#             */
/*   Updated: 2019/10/10 09:56:31 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	int	i;
	int	neg;
	int	r;

	i = 0;
	neg = 1;
	r = 0;
	while (nptr[i] == 32 || nptr[i] == '\f' || nptr[i] == '\n'
	|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = 10 * r + (nptr[i] - '0');
		i++;
	}
	return (neg * r);
}
