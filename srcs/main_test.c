/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnoirot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 12:05:07 by lnoirot           #+#    #+#             */
/*   Updated: 2020/03/10 12:06:41 by lnoirot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

int main()
{
	printf("%d\n", open("wood.xpm", O_RDONLY));
}
