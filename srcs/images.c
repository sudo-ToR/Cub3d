/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:01:40 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/25 10:44:14 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img
	*create_new_img(t_mlx *m, t_img *ptr, int width, int height)
{
	if (!(ptr->ref = mlx_new_image(m->mlx_ptr, width, height)))
		return (NULL);
	ptr->w = width;
	ptr->h = height;
	if (!(ptr->img = mlx_get_data_addr(ptr->ref, &ptr->bits_per_pixel, &ptr->size_line, &ptr->endian)))
		return (NULL);
	return (ptr);
}
