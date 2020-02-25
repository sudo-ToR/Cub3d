/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:00:02 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/11 18:26:06 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_putstr_m(char *str, int *i)
{
	int j;

	j = 0;
	if (str == NULL)
		return (j);
	while (str[j] && str[j] != '%')
	{
		ft_putchar(str[j]);
		j++;
	}
	*i += j;
	return (j);
}

int		ft_putnbr_base(int n, char c)
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
	{
		ft_putchar(base[(unsigned)n]);
		return (1);
	}
	else
	{
		l += ft_putnbr_base((unsigned)n / length, c);
		l += ft_putnbr_base((unsigned)n % length, c);
	}
	return (l);
}

int		ft_putnbr_base_d(int n, char *base)
{
	unsigned int	length;
	unsigned int	nbr;
	int				l;

	length = 0;
	l = 0;
	if (n < 0)
		nbr = -n;
	else
		nbr = n;
	while (base[length])
		length++;
	if (nbr < length)
	{
		ft_putchar(base[nbr]);
		return (1);
	}
	else
	{
		l += ft_putnbr_base_d(nbr / length, base);
		l += ft_putnbr_base_d(nbr % length, base);
	}
	return (l);
}

int		ft_putnbr_p(void *n)
{
	int				length;
	int				l;
	long long int	nb;
	char			*base;

	nb = (long long int)n;
	base = "0123456789abcdef";
	length = 16;
	l = 0;
	if (nb < length)
		return (write(1, &base[nb], 1));
	else
	{
		l += ft_putnbr_p((void *)(nb / length));
		l += ft_putnbr_p((void *)(nb % length));
	}
	return (l);
}
