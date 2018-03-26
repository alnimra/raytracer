/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 16:38:19 by mray              #+#    #+#             */
/*   Updated: 2018/02/26 16:38:19 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_gl		*create_gl(void *lib, void *surf)
{
	t_gl	*tmp;

	tmp = ft_memalloc(sizeof(t_gl));
	tmp->lib = lib;
	tmp->surf = surf;
	tmp->live_trans[0] = 1;
	tmp->live_trans[1] = 0;
	tmp->live_trans[2] = 0;
	tmp->live_trans[3] = 0.27015;
	tmp->live_trans[4] = 0;
	return (tmp);
}

t_canvas	*create_canvas(t_gl *gl)
{
	t_canvas *tmp;

	tmp = ft_memalloc(sizeof(t_canvas));
	tmp->img = mlx_new_image(gl->lib, WIDTH, HEIGHT);
	tmp->pix_data = mlx_get_data_addr(tmp->img, &(tmp->byte_size),
&(tmp->size_line), &(tmp->endian));
	return (tmp);
}
