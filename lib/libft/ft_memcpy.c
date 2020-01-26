/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:32:15 by lnoirot           #+#    #+#             */
/*   Updated: 2019/10/11 11:17:13 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*tmps;
	char	*tmpd;
	size_t	i;

	i = 0;
	tmps = (char *)src;
	tmpd = (char *)dest;
	if (tmps == NULL && tmpd == NULL)
		return (NULL);
	while (i < n)
	{
		tmpd[i] = tmps[i];
		i++;
	}
	return (dest);
}
