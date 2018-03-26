/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 21:29:05 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 21:29:05 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_intersection_plane(t_plane *plane, t_vec *vec)
{
	double a;
	double b;

	a = dot(plane->normal, vec->comp[1]);
	if (a == 0)
		return (-1);
	b = dot(plane->normal, sub(vec->comp[0],
multi(plane->normal, plane->dist)));
	return (-1 * (b / a));
}

t_plane		*create_plane(t_3dpt normal, double dist, t_color col)
{
	t_plane *tmp;

	tmp = (t_plane *)malloc(sizeof(t_plane));
	tmp->normal = normal;
	tmp->dist = dist;
	tmp->col = col;
	tmp->find_insct = find_intersection_plane;
	return (tmp);
}

void		parse_plane(t_gl *gl, char **obj_data, int j)
{
	char	**hd;
	t_3dpt	one;
	double	a;

	error_if_not(obj_data, 4);
	gl->obj_data[j]->type = "plane";
	hd = ft_strsplit(obj_data[1], ' ');
	error_if_not(hd, 3);
	one = create_3dpt(ft_atod(hd[0]), ft_atod(hd[1]), ft_atod(hd[2]));
	free_array((void **)hd);
	hd = ft_strsplit(obj_data[2], ' ');
	error_if_not(hd, 1);
	a = ft_atod(hd[0]);
	free_array((void **)hd);
	hd = ft_strsplit(obj_data[3], ' ');
	error_if_not(hd, 4);
	gl->obj_data[j]->obj = create_plane(one, a, create_color(ft_atod(hd[0]),
ft_atod(hd[1]), ft_atod(hd[2]), ft_atod(hd[3])));
	free_array((void **)hd);
}
