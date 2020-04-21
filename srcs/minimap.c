/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:20:56 by lnoirot           #+#    #+#             */
/*   Updated: 2020/04/21 11:54:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		draw_minimap(t_mlx m)
{
	m.render.img = mlx_get_data_addr(m.img_ptr, &(m.render.bits_per_pixel),
		&(m.render.size_line), &(m.render.endian));
	return (0);
}

void	draw_square(t_img *ptr, t_pos coord, unsigned int color, int width)
{
	t_pos square;

	square.y = coord.x;
	while (square.y < coord.x + width)
	{
		square.x = coord.y;
		while (square.x < coord.y + width)
		{
			draw_pixel_hex(ptr, square, color);
			square.x++;
		}
		square.y++;
	}
}

void	minimap(t_mlx *m)
{
	int			i;
	int			j;
	t_pos_fl	player_pos;

	i = -1;
	while (++i < m->p.height)
	{
		j = -1;
		while (m->p.map[i][++j])
		{
			if (m->p.map[i][j] == '1')
				draw_square(&m->minimap, (t_pos){i * 16, j * 16},
					0xff000000, 16);
			else
				draw_square(&m->minimap, (t_pos){i * 16, j * 16},
					0x00000000, 16);
		}
	}
	player_pos = (t_pos_fl) {
		.x = (double)m->pl.x * 16,
		.y = (double)m->pl.y * 16.
	};
	draw_square(&m->minimap, (t_pos){player_pos.y - 3.,
		player_pos.x - 3.}, 0x00ff0000, 6);
}
