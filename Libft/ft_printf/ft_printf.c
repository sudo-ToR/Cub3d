/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 15:15:35 by lnoirot           #+#    #+#             */
/*   Updated: 2020/01/21 18:05:04 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_converter_selector(char *str, int *ret, va_list ap, int j)
{
	if (str[j] == 'c')
		*ret += ft_converter_c(str, ap, 0);
	else if (str[j] == 's')
		*ret += ft_converter_s(str, ap);
	else if (str[j] == 'p')
		*ret += ft_converter_p(str, ap);
	else if (str[j] == 'd' || str[j] == 'i')
		*ret += ft_converter_d(str, ap);
	else if (str[j] == 'x' || str[j] == 'X' || str[j] == 'u')
		*ret += ft_converter_xu(str, ap, str[j]);
	else if (str[j] == '%')
		*ret += ft_converter_c(str, ap, 1);
}

int		ft_printf(const char *str, ...)
{
	int		ret;
	int		j;
	va_list	ap;

	ret = 0;
	j = 0;
	va_start(ap, str);
	while (*str)
	{
		str += ft_putstr_m((char *)str, &ret);
		if (*str == '%' && str++)
		{
			j = 0;
			while (ft_is_converter(str[j]) != 1 && str[j])
				j++;
			ft_converter_selector((char *)str, &ret, ap, j);
			while (ft_is_converter(*str) != 1)
				str++;
			str++;
		}
	}
	va_end(ap);
	return (ret);
}
