/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 19:32:19 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/11 18:10:26 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		count_d(int arg)
{
	unsigned int	nbr;
	int				ret;

	ret = 0;
	if (arg == 0)
		return (1);
	if (arg < 0)
		nbr = -arg;
	else
		nbr = arg;
	while (nbr > 0)
	{
		ret++;
		nbr /= 10;
	}
	return (ret);
}

int		count_xu(int n, int c)
{
	unsigned int	length;
	int				l;
	char			*base;

	length = 0;
	l = 0;
	base = (c == 'X') ? "0123456789ABCDEF" : "0123456789abcdef";
	if (c == 'u')
		base = "0123456789";
	while (base[length])
		length++;
	if ((unsigned)n < length)
		return (1);
	else
	{
		l += count_xu((unsigned)n / length, c);
		l += count_xu((unsigned)n % length, c);
	}
	return (l);
}

int		ft_count_p(void *n)
{
	int				l;
	long long int	nb;

	nb = (long long int)n;
	l = 2;
	if (n == NULL)
		return (3);
	while (nb > 0)
	{
		nb /= 16;
		l++;
	}
	return (l);
}
