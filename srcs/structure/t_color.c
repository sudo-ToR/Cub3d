/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 15:29:31 by lnoirot           #+#    #+#             */
/*   Updated: 2020/01/26 16:55:07 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color		create_color(UCHAR r, UCHAR g, UCHAR b, UCHAR a)
{
	t_color result;

	result.r = r;
	result.g = g;
	result.b = b;
	result.a = a;
	return (result);
}

t_color		*malloc_color(UCHAR r, UCHAR g, UCHAR b, UCHAR a)
{
	t_color *result;

	result = (t_color *)malloc(sizeof(t_color));
	if (result == NULL)
		return (NULL);

	*result = create_color(r, g, b, a);

	return (result);
}

void 		destroy_color(t_color to_destroy)
{
	(void)to_destroy;
}

void 		free_color(t_color *to_free)
{
	destroy_color(*to_free);
	free(to_free);
}
