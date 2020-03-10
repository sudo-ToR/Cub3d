/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <lnoirot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:01:40 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/10 19:52:05 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img
	*create_text(t_mlx *m, t_img *text, char *path)
{
	if (!(text->ref = mlx_xpm_file_to_image(m->mlx_ptr, path, &text->w, &text->h)))
		return (NULL);
	if (!(text->img = (mlx_get_data_addr(text->ref, &text->bits_per_pixel, &text->size_line, &text->endian))))
		return (NULL);
	return (text);
}

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

void
	draw_pixel(t_img *ref, t_pos pos, unsigned char color[3], t_mlx m)
{
	int calcul;
	unsigned int c;
	
	calcul = pos.y * ref->w + pos.x;
	c = (color[0] << 16) | (color[1] << 8) | (color[2]);
	((unsigned int *)ref->img)[calcul] = c;
}

void
	draw_pixel_hex(t_img *ref, t_pos pos, unsigned int hexcolor, t_mlx m)
{
	int calcul;

	calcul = (pos.y) * ref->w + pos.x;
	hexcolor = ((hexcolor & 0xff000000) >> 8) | ((hexcolor & 0xff0000) >> 8) | ((hexcolor & 0xff00) >> 8);
	((unsigned int *)ref->img)[calcul] = hexcolor;
}

void
	draw_square(t_mlx m, t_img *ptr, int i, int j, unsigned int color, int width)
{
	t_pos square;

	square.y = i;

	while (square.y < i + width)
	{

		square.x = j;
		while (square.x < j + width)
		{
			draw_pixel_hex(ptr, square, color, m);
			square.x++;
		}
		square.y++;
	}
}

unsigned char	*get_pixel_texture(t_img *texture, t_pos coord)
{
	int				index;

	index = texture->size_line * coord.y + coord.x;
	return ((unsigned char *)&texture->img[index]);
}

void
	draw_wall(t_img *render, t_pos pixel, char wall, t_mlx *m, double heigth)
	{
		double		ratio;
		t_pos		coord;

		ratio = m->ray.coord.x - (int)m->ray.coord.x;
		coord = (t_pos)
		{
			.x = ratio * m->no_text.w,
			.y = (pixel.y - m->ray.wall_coord.x) * (m->no_text.h / heigth)
		};
		if (m->cam_angle >= M_PI_4 && m->cam_angle <= 3. * M_PI_4)
		{
			draw_pixel(render, pixel, get_pixel_texture(&m->no_text, coord), *m);
		}
		else if (wall == 'V')
			draw_pixel_hex(render, pixel, 0xffff0000, *m);
		else if (wall == 'H')
			draw_pixel_hex(render, pixel, 0xffffffff, *m);
	}
	

void
	draw_column(double distance, t_mlx *m, int column_nbr, char wall)
{
	double				heigth;
	int					i;
	t_pos_fl			pos;
	t_pos				pixel;
	
	heigth =  (double)(m->p.r[1]) / distance;
	i = 0;
	m->ray.wall_coord.y = (double)(m->p.r[1] / 2.) + (heigth / 2.);
	m->ray.wall_coord.x = (double)(m->p.r[1] / 2.) - (heigth / 2.);
	pixel.x = floor(m->po.x - 1) + column_nbr;
	pos.y = 0.0;
	while (pos.y < m->p.r[1])
	{
		pixel.y = (int)pos.y;
		if (pos.y < m->ray.wall_coord.x)
			draw_pixel(&m->render, pixel, m->colors.ceil, *m);
		else if (pos.y <= m->ray.wall_coord.y && pos.y >= m->ray.wall_coord.x)
			draw_wall(&m->render, pixel, wall, m, heigth);
		else if (pos.y > m->ray.wall_coord.y)
			draw_pixel(&m->render, pixel, m->colors.floor, *m);
		pos.y += 1.;
	}
}