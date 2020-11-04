/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 16:09:08 by user42            #+#    #+#             */
/*   Updated: 2020/11/03 16:17:04 by user42           ###   ########.fr       */
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
	return (new);
}

void		lst_insert(t_sprites *tmp, t_list *prev, t_list *curs)
{
	t_list *sprites_to_insert;

	sprites_to_insert = ft_lstnew(tmp);
	prev->next = sprites_to_insert;
	sprites_to_insert->next = curs;
}
