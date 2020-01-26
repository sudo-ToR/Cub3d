/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 17:28:09 by lnoirot           #+#    #+#             */
/*   Updated: 2019/10/14 15:13:53 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int size;

	size = 0;
	if (n == -2147483648)
		return (11);
	if (n <= 0)
	{
		n = -n;
		size++;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

static int	ft_power_ten(int n)
{
	int p;

	p = 10;
	if (n == 0)
		return (1);
	while (n > 1)
	{
		p *= 10;
		n--;
	}
	return (p);
}

char		*ft_itoa(int n)
{
	unsigned int	nbis;
	unsigned int	nter;
	char			*r;
	int				i;
	int				size;

	size = ft_count(n);
	if (!(r = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	nbis = (unsigned)n;
	if (n < 0)
	{
		nbis = (unsigned)-n;
		r[i] = '-';
		i++;
	}
	while (i++ < size)
	{
		nter = nbis / ft_power_ten(size - i);
		r[i - 1] = (nter % 10) + '0';
	}
	r[i - 1] = '\0';
	return (r);
}
