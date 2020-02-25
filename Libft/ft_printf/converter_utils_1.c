/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 14:32:18 by lnoirot           #+#    #+#             */
/*   Updated: 2019/12/28 18:44:22 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init(t_flag *stock)
{
	stock->pre = 0;
	stock->width = 0;
	stock->min = 0;
	stock->zero = 0;
	stock->flag = 0;
	stock->star = 0;
}

t_flag	*ihatemoulinette(t_flag *stock, char *str, va_list ap)
{
	if (*str == '0')
		stock->zero = (*(++str) == '*') ? va_arg(ap, int) : ft_atoi(str);
	else if (ft_isdigit(*str) || *str == '*')
		stock->pre = (*str == '*') ? va_arg(ap, int) : ft_atoi(str);
	if (*str == '*' && stock->zero < 0 && (stock->min = abs(stock->zero)))
		stock->zero = 0;
	if (stock->pre < 0 && (stock->min = abs(stock->pre)))
		stock->pre = 0;
	return (stock);
}
