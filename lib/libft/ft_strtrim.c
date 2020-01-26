/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 10:11:43 by lnoirot           #+#    #+#             */
/*   Updated: 2019/10/15 11:34:38 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_set(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_set(char const *s1, char const *set)
{
	size_t	i;
	int		count;

	count = 0;
	while (s1[count] && find_set(s1[count], set) == 1)
		count++;
	if ((size_t)count == ft_strlen(s1))
		return (count);
	i = ft_strlen(s1) - 1;
	while (s1[i] && find_set(s1[i], set) == 1)
	{
		i--;
		count++;
	}
	return (count);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*r;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	if (s1 == 0 || set == 0)
		return (0);
	size = ft_strlen(s1) - count_set(s1, set);
	if (size == 0)
		return (ft_strdup(""));
	if (!(r = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	while (s1[i] && find_set(s1[i], set) == 1)
		i++;
	size = size + i;
	while (i < size)
	{
		r[j] = s1[i];
		i++;
		j++;
	}
	r[j] = '\0';
	return (r);
}
