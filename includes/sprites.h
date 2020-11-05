/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:26:29 by user42            #+#    #+#             */
/*   Updated: 2020/11/04 21:29:07 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

#include "structures.h"

t_sprites	*create_sprite(t_pos_fl coord, t_pos_fl pl, t_mlx *m);
void		lst_insert(t_sprites *tmp, t_list *prev, t_list *curs);
void		add_sprites(t_pos_fl coord, t_mlx *m);
void		draw_text_sp(t_coord_sprite sp, t_pos_fl tmp, t_pos_fl h_w, t_mlx *m);
double		calc_sp(t_sprites *cast, t_coord_sprite *hw_tmp, t_coord_sprite *sp, t_mlx *m);
void		draw_sprites(t_mlx *m);

#endif