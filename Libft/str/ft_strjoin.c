/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:43:16 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/15 12:10:27 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	int		j;

	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(r = (char *)malloc(sizeof(char)
		* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (*s1)
	{
		r[j] = *s1;
		s1++;
		j++;
	}
	while (*s2)
	{
		r[j] = *s2;
		s2++;
		j++;
	}
	r[j] = '\0';
	return (r);
}
