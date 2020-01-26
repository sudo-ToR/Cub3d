/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:24:36 by lnoirot           #+#    #+#             */
/*   Updated: 2019/10/18 12:16:02 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*array;
	char	*tmp;
	size_t	i;

	if (!(array = malloc(sizeof(void) * (size * count))))
		return (NULL);
	tmp = (char *)array;
	i = 0;
	while (i < (size * count))
	{
		tmp[i] = 0;
		i++;
	}
	return (array);
}
