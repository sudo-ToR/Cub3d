/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:50:17 by lnoirot           #+#    #+#             */
/*   Updated: 2020/11/01 22:59:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double		check_vert(t_mlx *m, double coeff, int dec)
{
	t_pos_fl	co;

	co.x = (dec == 1) ? floor(m->pl.x + dec) - m->pl.x + 0.000001
		: -(((double)m->pl.x - floor(m->pl.x)) + 0.000001);
	co.y = coeff * co.x;
	while (co.x + m->pl.x < m->p.width && co.y + m->pl.y < m->p.height)
	{
		if (co.y + m->pl.y < 0)
			return (FLT_MAX);
		if (m->p.map[(int)(co.y + m->pl.y)][(int)(co.x + m->pl.x)] == '1')
		{
			m->coord_vert.y = co.x + m->pl.x;
			m->coord_vert.x = co.y + m->pl.y;
			draw_pixel_hex(&m->minimap, (t_pos){(co.x + m->pl.x) * 16,
				(co.y + m->pl.y) * 16}, 0xffff0000);
			return (sqrt(pow(co.y, 2) + pow(co.x, 2)));
		}
		else if (m->p.map[(int)(co.y + m->pl.y)][(int)(co.x + m->pl.x)] == '2')
			add_sprites(co, m);
		co.x += (double)dec;
		co.y = coeff * co.x;
	}
	return (sqrt(pow(co.y, 2) + pow(co.x, 2)));
}

double		check_hor(t_mlx *m, double coeff, int dec)
{
	t_pos_fl co;

	co.y = (dec == 1) ? floor(m->pl.y + dec) - m->pl.y + 0.000001
		: (m->pl.y - floor(m->pl.y) + 0.000001) * (double)dec;
	co.x = co.y / coeff;
	while (co.y + m->pl.y < m->p.height && co.x + m->pl.x < m->p.width)
	{
		if (co.x + m->pl.x < 0. || coeff == 1.)
			return (FLT_MAX);
		if (m->p.map[(int)(co.y + m->pl.y)][(int)(co.x + m->pl.x)] == '1')
		{
			m->coord_hor.x = co.x + m->pl.x;
			m->coord_hor.y = co.y + m->pl.y;
			draw_pixel_hex(&m->minimap, (t_pos){(co.x + m->pl.x) * 16.0,
				(co.y + m->pl.y) * 16.0}, 0xffffffff);
			return (sqrt(pow(co.y, 2) + pow(co.x, 2)));
		}
		else if (m->p.map[(int)(co.y + m->pl.y)][(int)(co.x + m->pl.x)] == '2')
			add_sprites(co, m);
		co.y += dec;
		co.x = co.y / coeff;
	}
	return (sqrt(pow(co.y, 2) + pow(co.x, 2)));
}

void		draw_image(double cam_angle, t_mlx *m)
{
	double	angle;
	int		i;
	double	var_angle;
	double	distance;

	if (cam_angle < M_PI / 6.0)
		cam_angle += 2.0 * M_PI;
	angle = -(M_PI / 6.0) + cam_angle;
	var_angle = M_PI / 3. / m->p.r[0];
	i = 0;
	while (angle <= M_PI / 6. + cam_angle && i < m->p.r[0])
	{
		m->ray_angle = angle;
		adjust_cam_angle(&angle);
		distance = get_distance(angle, m);
		draw_column(distance, m, i);
		angle += var_angle;
		i++;
	}
	double 		dist_sprites;
	double		heigth;
	double		width;
	t_list		*cursor;
	t_sprites	*cast;
	t_pos_fl	beg_end;
	t_pos_fl	sp_coord;
	t_pos		pixel;
	double		tmp;
	
	cursor = m->sprites;
	while (cursor)
	{
		cast = (t_sprites *)cursor->content;
		dist_sprites = cast->distance;
		heigth = (double)(m->p.r[1]) / dist_sprites;
		width = (double)m->s_text.w * heigth / (double)m->s_text.h;
		beg_end.x = (m->cam_angle - (M_PI / 6.) + atan((cast->coord.y - m->pl.y) / (cast->coord.x - m->pl.x))) * (m->p.r[0] / (M_PI * 3.)) - (width / 2.);
		beg_end.y = (m->cam_angle - (M_PI / 6.) + atan((cast->coord.y - m->pl.y) / (cast->coord.x - m->pl.x))) * (m->p.r[0] / (M_PI * 3.)) + (width / 2.);
		sp_coord.y = (double)(m->p.r[1] / 2.) + (heigth / 2.);
		sp_coord.x = (double)(m->p.r[1] / 2.) - (heigth / 2.); 
		tmp = sp_coord.x;
		pixel.y = (int) beg_end.x;
		while (pixel.y < (int)beg_end.y)
		{
			while (sp_coord.x < sp_coord.y && pixel.y >= 0 && pixel.y <= m->p.r[0])
			{
				if (sp_coord.x > m->p.r[1] && sp_coord.x < 0)
					break;
				pixel.x = (int)sp_coord.x;
				draw_pixel_hex(&m->render, pixel, 0xffffff);
				sp_coord.x += 1.;
			}
			sp_coord.x = tmp;
			pixel.y += 1.;
		}
		cursor = cursor->next;
	}
	
	ft_lstclear(&m->sprites, free);
}

double		get_distance(double angle, t_mlx *m)
{
	double		coeff;
	t_pos_fl	distance;
	t_pos		inc;
	t_pos		coord;

	coord = (t_pos) {0, 0};
	coeff = tan(angle);
	inc.x = (angle >= M_PI_2 && angle <= 3. * M_PI_2) ? -1 : 1;
	inc.y = (angle >= M_PI && angle <= 2. * M_PI) ? -1 : 1;
	distance.x = check_vert(m, coeff, inc.x) * cos(m->cam_angle - angle);
	distance.y = check_hor(m, coeff, inc.y) * cos(m->cam_angle - angle);
	if (distance.x > distance.y)
	{
		m->ray.coord = (t_pos_fl)m->coord_hor;
		m->ray.dir_wall = 0;
	}
	else
	{
		m->ray.coord = (t_pos_fl)m->coord_vert;
		m->ray.dir_wall = 1;
	}
	return (fmin(distance.x, distance.y));
}
