/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:26:29 by user42            #+#    #+#             */
/*   Updated: 2020/11/01 14:34:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITES_H
# define SPRITES_H

#include "structures.h"

t_sprites	*create_sprite(t_pos_fl coord, t_pos_fl pl);
void		lst_insert(t_sprites *tmp, t_list *prev, t_list *curs);
void		add_sprites(t_pos_fl coord, t_mlx *m);

#endif