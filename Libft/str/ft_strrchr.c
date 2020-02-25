/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 18:49:52 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/15 12:24:25 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;
	char	*tmp;

	tmp = (char *)s;
	size = ft_strlen(tmp);
	while (size != 0 && tmp[size] != c)
		size--;
	if (tmp[size] != c)
		return (NULL);
	return (&tmp[size]);
}
