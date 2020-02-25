/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 16:40:14 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/11 18:12:05 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flag		*ft_trouveunnom(t_flag *stock, int *len, int b, int c)
{
	if (stock->width < 0 && stock->zero)
		b = 1;
	*len = count_d(stock->arg);
	if (stock->flag && stock->width && !(stock->arg))
		stock->flag = 0;
	*len -= (stock->flag && !(stock->arg)) ? 1 : 0;
	stock->width = (stock->width < 0) ? 0 : stock->width;
	if (c && stock->zero && !(b) && (stock->pre = stock->zero))
		stock->zero = 0;
	stock->width -= (stock->width) ? *len : 0;
	*len += (stock->arg < 0) ? 1 : 0;
	stock->pre -= (stock->width > 0) ? *len + stock->width : *len;
	if (stock->width < 0)
		stock->width = 0;
	stock->min -= *len + stock->width;
	stock->zero -= *len;
	return (stock);
}

int			ft_parsing(t_flag *stock, va_list ap, char *str, int len)
{
	int b;
	int c;

	b = 0;
	c = 0;
	stock = ihatemoulinette(stock, str, ap);
	if (*str == '-' && (str++))
	{
		if (*str == '0')
			str++;
		stock->min = (*str == '*') ? abs(va_arg(ap, int)) : ft_atoi(str);
	}
	while (ft_isdigit(*str) || *str == '*')
		str++;
	if (*str == '.' && (stock->flag = 1))
	{
		c = 1;
		stock->width = (*(++str) == '*') ? va_arg(ap, int) : ft_atoi(str);
	}
	stock->arg = va_arg(ap, int);
	stock = ft_trouveunnom(stock, &len, b, c);
	return (len);
}

int			ft_parsing_x(int len, int ret, t_flag stock, char c)
{
	stock.width -= (stock.width) ? len : 0;
	stock.pre -= (stock.width > 0) ? len + stock.width : len;
	if (stock.width < 0)
		stock.width = 0;
	stock.min -= len + stock.width;
	stock.zero -= len;
	while (stock.zero-- > 0)
		ret += write(1, "0", 1);
	while (stock.pre > 0 && (stock.pre--))
		ret += write(1, " ", 1);
	while (stock.width > 0 && (stock.width--))
		ret += write(1, "0", 1);
	ret += (stock.arg) ? ft_putnbr_base(stock.arg, c) : 0;
	ret += (!(stock.arg) && !(stock.flag)) ? write(1, "0", 1) : 0;
	while (stock.min-- > 0)
		ret += write(1, " ", 1);
	return (ret);
}

t_flag		ft_converter_xu_pt1(char *str, t_flag stock, va_list ap, int *d)
{
	if (*str == '0')
		stock.zero = (*(++str) == '*') ? va_arg(ap, int) : ft_atoi(str);
	else if (ft_isdigit(*str) || *str == '*')
		stock.pre = (*str == '*') ? va_arg(ap, int) : ft_atoi(str);
	if (*str == '*' && stock.zero < 0 && (stock.min = abs(stock.zero)))
		stock.zero = 0;
	if (stock.pre < 0 && (stock.min = abs(stock.pre)))
		stock.pre = 0;
	if (*str == '-' && (str++))
		stock.min = (*str == '*') ? abs(va_arg(ap, int)) : ft_atoi(str);
	while (ft_isdigit(*str) || *str == '*')
		str++;
	if (*str == '.' && (stock.flag = 1))
	{
		*d = 1;
		stock.width = (*(++str) == '*') ? va_arg(ap, int) : ft_atoi(str);
	}
	stock.arg = va_arg(ap, int);
	return (stock);
}

void		ft_converter_s_pt1(char **tmp, va_list ap, t_flag *stock)
{
	*tmp = va_arg(ap, char *);
	if (*tmp == NULL)
		*tmp = "(null)";
	if ((stock->width < (int)ft_strlen(*tmp) && (!(stock->width) && !(stock->flag)))
			|| stock->width > (int)ft_strlen(*tmp))
		stock->width = (int)ft_strlen(*tmp);
	if (stock->width < 0)
		stock->width = (int)ft_strlen(*tmp);
}
