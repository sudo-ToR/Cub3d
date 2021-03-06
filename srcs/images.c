/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 20:01:40 by lnoirot           #+#    #+#             */
/*   Updated: 2020/11/14 16:40:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_img	*create_new_img(t_mlx *m, t_img *ptr, int width, int height)
{
	if (!(ptr->ref = mlx_new_image(m->mlx_ptr, width, height)))
		return (NULL);
	ptr->w = width;
	ptr->h = height;
	if (!(ptr->img = mlx_get_data_addr(ptr->ref, &ptr->bits_per_pixel,
		&ptr->size_line, &ptr->endian)))
		return (NULL);
	return (ptr);
}

void	draw_pixel(t_img *ref, t_pos pos, char color[3])
{
	int	index;

	index = ref->size_line * pos.y + (ref->bits_per_pixel / 8) * pos.x;
	ref->img[index] = color[0];
	ref->img[index + 1] = color[1];
	ref->img[index + 2] = color[2];
}

void	draw_pixel_hex(t_img *ref, t_pos pos, unsigned int hexcolor)
{
	int calcul;

	calcul = (pos.y) * ref->w + pos.x;
	hexcolor = ((hexcolor & 0xff000000) >> 8) | ((hexcolor & 0xff0000) >> 8)
		| ((hexcolor & 0xff00) >> 8);
	((unsigned int *)ref->img)[calcul] = hexcolor;
}

void	draw_wall(t_img *render, t_pos pixel, t_mlx *m, double heigth)
{
	double		ratio;
	t_img		*texture;
	t_pos		coord;

	ratio = m->ray.coord.x - floor(m->ray.coord.x);
	texture = NULL;
	select_texture(&texture, m);
	coord = (t_pos)
	{
		.x = ratio * texture->w,
		.y = (pixel.y - m->ray.wall_coord.x) * (double)texture->h / heigth
	};
	draw_pixel(render, pixel, get_pixel_texture(texture, coord));
}

void	draw_column(double distance, t_mlx *m, int column_nbr)
{
	double				heigth;
	t_pos_fl			pos;
	t_pos				pixel;

	heigth = (double)(m->p.r[1]) / distance;
	m->ray.wall_coord.y = (double)(m->p.r[1] / 2.) + (heigth / 2.);
	m->ray.wall_coord.x = (double)(m->p.r[1] / 2.) - (heigth / 2.);
	pixel.x = column_nbr;
	pos.y = 0.;
	while (pos.y < m->p.r[1])
	{
		pixel.y = (int)pos.y;
		if (pos.y < m->ray.wall_coord.x)
			draw_pixel(&m->render, pixel, m->colors.ceil);
		else if (pos.y <= m->ray.wall_coord.y && pos.y >= m->ray.wall_coord.x)
			draw_wall(&m->render, pixel, m, heigth);
		else if (pos.y > m->ray.wall_coord.y)
			draw_pixel(&m->render, pixel, m->colors.floor);
		pos.y += 1.;
	}
}
