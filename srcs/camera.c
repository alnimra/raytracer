/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 12:17:22 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 12:17:22 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_cam	*create_cam(t_3dpt org, t_3dpt dir, t_3dpt right, t_3dpt down)
{
	t_cam *tmp;

	tmp = (t_cam *)malloc(sizeof(t_cam));
	tmp->prop[0] = org;
	tmp->prop[1] = dir;
	tmp->prop[2] = right;
	tmp->prop[3] = down;
	return (tmp);
}

void	parse_cam(t_gl *gl, char **obj_data, int j)
{
	char **hd;

	if (!obj_data[2])
		errorify("Not a valid file");
	gl->obj_data[j]->type = "cam";
	(gl->obj_data[j]->obj) = (t_cam *)malloc(sizeof(t_cam));
	hd = ft_strsplit(obj_data[1], ' ');
	if (!hd[2])
		errorify("Not a valid file");
	((t_cam *)(gl->obj_data[j]->obj))->prop[0] =
		create_3dpt(ft_atod(hd[0]), ft_atod(hd[1]), ft_atod(hd[2]));
	free_array((void **)hd);
	hd = ft_strsplit(obj_data[2], ' ');
	if (!hd[2])
		errorify("Not a valid file");
	((t_cam *)(gl->obj_data[j]->obj))->prop[1] =
		normal(sub(create_3dpt(ft_atoi(hd[0]), ft_atoi(hd[1]), ft_atoi(hd[2])),
				((t_cam *)(gl->obj_data[j]->obj))->prop[0]));
	free_array((void **)hd);
}
