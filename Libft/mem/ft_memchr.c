/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:36:38 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/15 13:47:18 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmps;
	size_t			i;

	tmps = (unsigned char *)s;
	i = 0;
	while (i < n && tmps[i] != (unsigned char)c)
	{
		s++;
		i++;
	}
	if (i == n)
		return (NULL);
	return ((void *)s);
}
