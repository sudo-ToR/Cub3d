/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:20:56 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/23 20:28:58 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		draw_minimap(t_mlx m)
{
	m.render.img = mlx_get_data_addr(m.img_ptr, &(m.render.bits_per_pixel),
		&(m.render.size_line), &(m.render.endian));
	return(0);
}