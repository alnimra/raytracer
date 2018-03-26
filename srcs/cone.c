/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 15:18:19 by mray              #+#    #+#             */
/*   Updated: 2018/03/23 15:18:19 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_intersection_cone(t_cone *cone, t_vec *vec)
{
	double t[2];
	double coef[3];

	t[0] = sin(cone->tilt);
	t[1] = cos(cone->tilt);
	coef[0] = pow(t[1], 2) * squ(sub(vec->comp[1], multi(cone->vec->comp[1],
dot(vec->comp[1], cone->vec->comp[1])))) - pow(t[0], 2) * dot(vec->comp[1],
cone->vec->comp[1]) * dot(vec->comp[1], cone->vec->comp[1]);
	coef[1] = 2 * pow(t[1], 2) * dot(sub(vec->comp[1], multi(cone->vec->comp[1],
dot(vec->comp[1], cone->vec->comp[1]))), sub(sub(vec->comp[0],
cone->vec->comp[0]), multi(cone->vec->comp[1], dot(sub(vec->comp[0],
cone->vec->comp[0]), cone->vec->comp[1])))) - 2 * pow(t[0], 2) *
dot(vec->comp[1], cone->vec->comp[1]) * dot(sub(vec->comp[0],
cone->vec->comp[0]), cone->vec->comp[1]);
	coef[2] = pow(t[1], 2) * squ(sub(sub(vec->comp[0], cone->vec->comp[0]),
multi(cone->vec->comp[1], dot(sub(vec->comp[0], cone->vec->comp[0]),
cone->vec->comp[1])))) - pow(t[0], 2) * dot(sub(vec->comp[0],
cone->vec->comp[0]), cone->vec->comp[1]) * dot(sub(vec->comp[0],
cone->vec->comp[0]), cone->vec->comp[1]);
	return (solve_for_roots(coef));
}

t_cone		*create_cone(t_3dpt org, t_3dpt dir, double tilt, t_color col)
{
	t_cone *tmp;

	tmp = (t_cone *)malloc(sizeof(t_cone));
	tmp->vec = create_vec(org, dir);
	tmp->tilt = tilt;
	tmp->col = col;
	tmp->find_insct = find_intersection_cone;
	return (tmp);
}

t_3dpt		cone_get_normal_at(t_cone *cone, t_3dpt pt)
{
	t_3dpt norm;

	norm = sub(pt, cone->vec->comp[0]);
	norm = normal(
		sub(norm, multi(cone->vec->comp[1], dot(cone->vec->comp[1], norm))));
	return (norm);
}

void		parse_cone_2(char ***hd, char ***hd2, t_3dpt *one, char **obj_data)
{
	(*hd) = ft_strsplit(obj_data[1], ' ');
	(*hd2) = ft_strsplit(obj_data[5], ' ');
	error_if_not(*hd, 3);
	error_if_not(*hd2, 3);
	*one = create_3dpt(ft_atod((*hd)[0]) + ft_atod((*hd2)[0]),
ft_atod((*hd)[1]) + ft_atod((*hd2)[1]), ft_atod((*hd)[2]) + ft_atod((*hd2)[2]));
	free_array((void **)(*hd));
	free_array((void **)(*hd2));
	(*hd) = ft_strsplit(obj_data[2], ' ');
	(*hd2) = ft_strsplit(obj_data[6], ' ');
	error_if_not(*hd, 3);
	error_if_not(*hd2, 3);
}

void		parse_cone(t_gl *gl, char **obj_data, int j)
{
	char	**hd;
	char	**hd2;
	t_3dpt	one;
	t_3dpt	two;
	double	a;

	error_if_not(obj_data, 7);
	gl->obj_data[j]->type = "cone";
	parse_cone_2(&hd, &hd2, &one, obj_data);
	two = create_3dpt(ft_atod(hd[0]) + ft_atod(hd2[0]), ft_atod(hd[1]) +
ft_atod(hd2[1]), ft_atod(hd[2]) + ft_atod(hd2[2]));
	free_array((void **)hd);
	free_array((void **)hd2);
	hd = ft_strsplit(obj_data[3], ' ');
	error_if_not(hd, 1);
	a = ft_atod(hd[0]);
	free_array((void **)hd);
	hd = ft_strsplit(obj_data[4], ' ');
	error_if_not(hd, 4);
	gl->obj_data[j]->obj = create_cone(one, normal(two), a, create_color(
ft_atod(hd[0]), ft_atod(hd[1]), ft_atod(hd[2]), ft_atod(hd[3])));
	free_array((void **)hd);
}
