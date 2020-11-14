/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:23:16 by user42            #+#    #+#             */
/*   Updated: 2020/11/10 21:35:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	add_sprites(t_pos_fl coord, t_mlx *m)
{
	t_sprites	*tmp;
	t_sprites	*cast;
	t_list		*cursor;
	t_list		*previous;

	if (!(tmp = create_sprite(coord, m->pl, m)))
		return ;
	cursor = m->sprites;
	previous = NULL;
	cast = (cursor) ? (t_sprites *)(cursor->content) : NULL;
	while (cursor && cast->distance >= tmp->distance)
	{
		if (cast->coord.x == tmp->coord.x && cast->coord.y == tmp->coord.y)
		{
			free(tmp);
			return ;
		}
		previous = cursor;
		cursor = cursor->next;
		cast = (cursor) ? (t_sprites *)(cursor->content) : NULL;
	}
	if (!previous || !(m->sprites))
		ft_lstadd_front(&m->sprites, ft_lstnew(tmp));
	else
		lst_insert(tmp, previous, cursor);
}

void	draw_text_sprites(t_coord_sprite sp, t_pos_fl t, t_pos_fl h_w, t_mlx *m)
{
	t_pos	coord_text;
	char	*color;

	coord_text.x = (sp.column.x - t.y) * (m->s_text.h / h_w.x);
	coord_text.y = (sp.lines.x - t.x) * (m->s_text.w / h_w.y);
	color = get_pixel_texture(&m->s_text, coord_text);
	if (color[0] && color[1] && color[2] && color[3])
		draw_pixel(&m->render, (t_pos){sp.column.x, sp.lines.x}, color);
}

double		calc_sp(t_sprites *c, t_coord_sprite *h_t, t_coord_sprite *s, t_mlx *m)
{
	double		dist_sprites;

	dist_sprites = c->distance * cos(c->angle);
	h_t->column.x = (double)(m->p.r[1]) / dist_sprites;
	h_t->column.y = (double)m->s_text.w *
		h_t->column.x / (double)m->s_text.h;
	s->column.x = (c->angle + (M_PI / 6.)) *
		(m->p.r[0] / (M_PI / 3.)) - (h_t->column.y / 2.);
	s->column.y = (c->angle + (M_PI / 6.)) *
		(m->p.r[0] / (M_PI / 3.)) + (h_t->column.y / 2.);
	s->lines.x = (double)(m->p.r[1] / 2.) - (h_t->column.x / 2.);
	s->lines.y = (double)(m->p.r[1] / 2.) + (h_t->column.x / 2.);
	h_t->lines.x = s->lines.x;
	h_t->lines.y = s->column.x;
	return (dist_sprites);
}

void	draw_sprites(t_mlx *m)
{
	t_list			*cursor;
	t_sprites		*cast;
	t_coord_sprite	sp;
	t_coord_sprite	hw_tmp;
	double			dist_sp;
	t_list			*f;

	cursor = m->sprites;
	while (cursor)
	{
		cast = (t_sprites *)cursor->content;
		dist_sp = calc_sp(cast, &hw_tmp, &sp, m);
		while (sp.column.x < sp.column.y)
		{
			while (sp.lines.x < sp.lines.y && sp.column.x >= 0
				&& sp.column.x < m->p.r[0] && dist_sp < m->distance.distance[(int)sp.column.x])
			{
				if (sp.lines.x >= 0 && sp.lines.x < m->p.r[1])
					draw_text_sprites(sp, hw_tmp.lines, hw_tmp.column, m);
				sp.lines.x += 1.;
			}
			sp.column.x += 1.;
			sp.lines.x = hw_tmp.lines.x;
		}
		f = cursor;
		cursor = cursor->next;
	}
	ft_lstclear(&m->sprites, free);
}
