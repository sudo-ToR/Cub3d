/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 12:07:11 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/11 18:27:23 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include "../libft.h"

typedef struct	s_flag
{
	int			zero;
	int			min;
	int			width;
	int			pre;
	int			arg;
	int			flag;
	long int	star;
}				t_flag;

int				ft_printf(const char *str, ...);
int				ft_putnbr_base(int n, char c);
int				ft_putnbr_base_d(int n, char *base);
void			ft_putchar(char c);
int				ft_putstr_m(char *str, int *i);
int				ft_putnbr_p(void *n);
int				ft_isdigit(int c);
int				abs(int x);
int				count_d(int arg);
int				count_xu(int n, int c);
int				ft_count_p(void *n);
int				ft_is_converter(char c);
int				ft_converter_c(char *str, va_list ap, int i);
int				ft_converter_p(char *str, va_list ap);
int				ft_converter_d(char *str, va_list ap);
int				ft_parsing(t_flag *stock, va_list ap, char *str, int len);
t_flag			*ihatemoulinette(t_flag *stock, char *str, va_list ap);
void			ft_init(t_flag *stock);
int				ft_converter_xu(char *str, va_list ap, char c);
t_flag			ft_converter_xu_pt1(char *str, t_flag stock,
					va_list ap, int *d);
int				ft_parsing_x(int len, int ret, t_flag stock, char c);
void			ft_converter_s_pt1(char **tmp, va_list ap, t_flag *stock);
int				ft_converter_s(char *str, va_list ap);

#endif
