/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:50:17 by lnoirot           #+#    #+#             */
/*   Updated: 2020/10/31 23:31:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <float.h>

t_sprites	*create_sprite(t_pos_fl coord, t_pos_fl pl)
{
	t_sprites	*new;

	if (!(new = malloc(sizeof(t_sprites))))
		return(0);
	new->coord.x = (int)(coord.x + pl.x) + 0.5;
	new->coord.y = (int)(coord.y + pl.y) + 0.5;
	new->distance = sqrt(pow(new->coord.y, 2) + pow(new->coord.x, 2));
	return (new);
}

void		add_sprites(t_pos_fl coord, t_mlx *m)
{
	t_sprites	*tmp;
	t_list		*sprites_to_insert;
	t_sprites	*cast;
	t_list		*cursor;
	t_list		*previous;

	tmp = create_sprite(coord, m->pl);
	cursor = m->sprites;
	previous = NULL;
	if (!(m->sprites))
	{
		ft_lstadd_front(&m->sprites, ft_lstnew(tmp));
		return;
	}
	cast = (t_sprites *)(cursor->content);
	while (cursor && cast->distance >= tmp->distance)
	{
		cast = (t_sprites *)(cursor->content);
		if (cast->coord.x == tmp->coord.x && cast->coord.y == tmp->coord.y)
		{
			free (tmp);
			return;
		}
		previous = cursor;
		cursor = cursor->next;
	}
	if (!previous)
		ft_lstadd_front(&m->sprites, ft_lstnew(tmp));
	else
	{
		sprites_to_insert = ft_lstnew(tmp);
		previous->next = sprites_to_insert;
		sprites_to_insert->next = cursor;
	}	
}

double		check_vert(t_mlx *m, double coeff, int dec)
{
	t_pos_fl	coord;

	coord.x = (dec == 1) ? floor(m->pl.x + dec) - m->pl.x + 0.000001
		: -(((double)m->pl.x - floor(m->pl.x)) + 0.000001);
	coord.y = coeff * coord.x;
	while (coord.x + m->pl.x < m->p.width && coord.y + m->pl.y < m->p.height)
	{
		if (coord.y + m->pl.y < 0)
			return (FLT_MAX);
		if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '1')
		{
			m->coord_vert.y = coord.x + m->pl.x;
			m->coord_vert.x = coord.y + m->pl.y;
			draw_pixel_hex(&m->minimap, (t_pos){(coord.x + m->pl.x) * 16,
				(coord.y + m->pl.y) * 16}, 0xffff0000);
			return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
		}
		else if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '2')
			add_sprites(coord, m);
		coord.x += (double)dec;
		coord.y = coeff * coord.x;
	}
	return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
}

double		check_hor(t_mlx *m, double coeff, int dec)
{
	t_pos_fl coord;

	coord.y = (dec == 1) ? floor(m->pl.y + dec) - m->pl.y + 0.000001
		: (m->pl.y - floor(m->pl.y) + 0.000001) * (double)dec;
	coord.x = coord.y / coeff;
	while (coord.y + m->pl.y < m->p.height && coord.x + m->pl.x < m->p.width)
	{
		if (coord.x + m->pl.x < 0. || coeff == 1.)
			return (FLT_MAX);
		if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '1')
		{
			m->coord_hor.x = coord.x + m->pl.x;
			m->coord_hor.y = coord.y + m->pl.y;
			draw_pixel_hex(&m->minimap, (t_pos){(coord.x + m->pl.x) * 16.0,
				(coord.y + m->pl.y) * 16.0}, 0xffffffff);
			return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
		}
		else if (m->p.map[(int)(coord.y + m->pl.y)][(int)(coord.x + m->pl.x)] == '2')
			add_sprites(coord, m);
		coord.y += dec;
		coord.x = coord.y / coeff;
	}
	return (sqrt(pow(coord.y, 2) + pow(coord.x, 2)));
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
	ft_lstclear(&m->sprites, free);
}


void	ft_affichage(void *content)
{
	t_sprites	*x;

	x = (t_sprites *)content;

	// printf("x = %f\ty = %f  ====>", x->coord.x, x->coord.y); 
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
	ft_lstiter(m->sprites, ft_affichage);
	// printf("\n");
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
