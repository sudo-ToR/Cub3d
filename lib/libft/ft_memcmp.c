/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:39:13 by lnoirot           #+#    #+#             */
/*   Updated: 2019/10/10 14:19:13 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*tmp1;
	char	*tmp2;

	i = 0;
	tmp1 = (char *)s1;
	tmp2 = (char *)s2;
	if (n == 0)
		return (0);
	while (tmp1[i] == tmp2[i] && i < n - 1)
		i++;
	return ((unsigned char)tmp1[i] - (unsigned char)tmp2[i]);
}
