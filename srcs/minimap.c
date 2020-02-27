/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:20:56 by lnoirot           #+#    #+#             */
/*   Updated: 2020/02/27 11:53:16 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		draw_minimap(t_mlx m)
{
	m.render.img = mlx_get_data_addr(m.img_ptr, &(m.render.bits_per_pixel),
		&(m.render.size_line), &(m.render.endian));
	return(0);
}

void
	minimap(t_mlx m, double cam_angle)
{
	int i;
	int j;

	i = 0;
	while (i < m.p.height)
	{
		j = 0;
		while (m.p.map[i][j])
		{
			if (m.p.map[i][j] == '1')
				draw_square(m, &m.minimap, i * 16, j * 16, 0xff000000, 16);
			j++;
		}
		i++;
	}
	t_pos_fl player_pos;
	player_pos = (t_pos_fl) {
		.x = (double)m.pl.x * 16,
		.y = (double)m.pl.y * 16.
	};
	// printf("Player is at pos %.2f %.2f\n", (double)m.pl.x, (double)m.pl.y);
	draw_square(m, &m.minimap, (int)(player_pos.y - 3.), (int)(player_pos.x - 3.), 0x00ff0000, 6);
}