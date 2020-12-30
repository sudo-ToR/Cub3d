/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:09:08 by user42            #+#    #+#             */
/*   Updated: 2020/12/30 15:01:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_sprites	*create_sprite(t_pos_fl coord, t_pos_fl pl, t_mlx *m)
{
	t_sprites	*new;
	t_pos_fl	vec_cam;
	t_pos_fl	vec_sp;

	if (!(new = malloc(sizeof(t_sprites))))
		return (0);
	vec_cam.x = cos(m->cam_angle);
	vec_cam.y = sin(m->cam_angle);
	new->coord.x = (int)(coord.x + pl.x) + 0.5;
	new->coord.y = (int)(coord.y + pl.y) + 0.5;
	vec_sp.x = new->coord.x - pl.x;
	vec_sp.y = new->coord.y - pl.y;
	new->distance = sqrt(pow(new->coord.x - pl.x, 2)
		+ pow(new->coord.y - pl.y, 2));
	new->angle = acos((vec_cam.x * vec_sp.x + vec_cam.y * vec_sp.y)
		/ (sqrt(pow(vec_cam.x, 2) + pow(vec_cam.y, 2))
			* sqrt(pow(vec_sp.x, 2) + pow(vec_sp.y, 2))));
	new->angle *= (vec_cam.x * vec_sp.y - vec_cam.y * vec_sp.x >= 0) ? 1 : -1;
	new->distance *= cos(new->angle);
	if (fabs(new->angle) > 1.)
		new = NULL;
	return (new);
}

void		lst_insert(t_sprites *tmp, t_list *prev, t_list *curs)
{
	t_list *sprites_to_insert;

	sprites_to_insert = ft_lstnew(tmp);
	prev->next = sprites_to_insert;
	sprites_to_insert->next = curs;
}

void		find_map_width(t_pars *p)
{
	int i;

	i = -1;
	while (p->map[++i])
		p->width = ((int)ft_strlen(p->map[i]) > p->width) ?
			ft_strlen(p->map[i]) : p->width;
}

int			empty_line_parsing(char *line, t_pars *p, t_mlx *m)
{
	free(line);
	if (p->map)
		return (aff_error(WRONG_MAP, m));
	return (0);
}

void		square_map(t_pars *p)
{
	int		i;
	char	*tmp;
	int		len;

	i = -1;
	while (p->map[++i])
	{
		len = ft_strlen(p->map[i]);
		if (len < p->width)
		{
			tmp = ft_calloc(sizeof(char), (p->width + 1));
			ft_strlcpy(tmp, p->map[i], len + 1);
			free(p->map[i]);
			while (len < p->width + 1)
			{
				tmp[len] = '1';
				len++;
			}
			p->map[i] = tmp;
		}
	}
}
