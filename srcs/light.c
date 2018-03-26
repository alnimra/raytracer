/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:26:19 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 19:26:19 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light	*create_light(t_3dpt org, t_color col)
{
	t_light *tmp;

	tmp = (t_light *)malloc(sizeof(t_light));
	tmp->org = org;
	tmp->col = col;
	return (tmp);
}

void	parse_light(t_gl *gl, char **obj_data, int j)
{
	char **hd;

	if (!obj_data[2])
		errorify("Not a valid file");
	gl->obj_data[j]->type = "light";
	(gl->obj_data[j]->obj) = (t_light *)malloc(sizeof(t_light));
	hd = ft_strsplit(obj_data[1], ' ');
	if (!hd[2])
		errorify("Not a valid file");
	((t_light *)(gl->obj_data[j]->obj))->org =
		create_3dpt(ft_atod(hd[0]), ft_atod(hd[1]), ft_atod(hd[2]));
	free_array((void **)hd);
	hd = ft_strsplit(obj_data[2], ' ');
	if (!hd[3])
		errorify("Not a valid file");
	((t_light *)(gl->obj_data[j]->obj))->col = create_color(
		ft_atod(hd[0]), ft_atod(hd[1]), ft_atod(hd[2]), ft_atod(hd[3]));
	free_array((void **)hd);
}
