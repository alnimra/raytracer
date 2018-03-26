/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:01:00 by mray              #+#    #+#             */
/*   Updated: 2018/03/22 16:01:00 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_intersection_cyl(t_cyl *cyl, t_vec *vec)
{
	double coef[3];

	coef[0] = squ(sub(vec->comp[1], multi(cyl->vec->comp[1], dot(vec->comp[1],
cyl->vec->comp[1]))));
	coef[1] = 2 * dot(sub(vec->comp[1], multi(cyl->vec->comp[1],
dot(vec->comp[1], cyl->vec->comp[1]))), sub(sub(vec->comp[0],
cyl->vec->comp[0]), multi(cyl->vec->comp[1], dot(sub(vec->comp[0],
cyl->vec->comp[0]), cyl->vec->comp[1]))));
	coef[2] = squ(sub(sub(vec->comp[0], cyl->vec->comp[0]), multi(
cyl->vec->comp[1], dot(sub(vec->comp[0], cyl->vec->comp[0]),
cyl->vec->comp[1])))) - (cyl->rad * cyl->rad);
	return (solve_for_roots(coef));
}

t_cyl		*create_cyl(t_3dpt org, t_3dpt dir, double rad, t_color col)
{
	t_cyl *tmp;

	tmp = (t_cyl *)malloc(sizeof(t_cyl));
	tmp->vec = create_vec(org, dir);
	tmp->rad = rad;
	tmp->col = col;
	tmp->find_insct = find_intersection_cyl;
	return (tmp);
}

t_3dpt		cyl_get_normal_at(t_cyl *cyl, t_3dpt pt)
{
	t_3dpt norm;

	norm = sub(pt, cyl->vec->comp[0]);
	norm = normal(sub(norm, multi(cyl->vec->comp[1],
dot(cyl->vec->comp[1], norm))));
	return (norm);
}

void		parse_cyl_2(char ***hd, char ***hd2, t_3dpt *two, char **obj_data)
{
	free_array((void **)(*hd));
	free_array((void **)(*hd2));
	(*hd) = ft_strsplit(obj_data[2], ' ');
	(*hd2) = ft_strsplit(obj_data[6], ' ');
	error_if_not(*hd, 3);
	error_if_not(*hd2, 3);
	*two = create_3dpt(ft_atod((*hd)[0]) + ft_atod((*hd2)[0]),
ft_atod((*hd)[1]) + ft_atod((*hd2)[1]), ft_atod((*hd)[2]) + ft_atod((*hd2)[2]));
	free_array((void **)(*hd));
	free_array((void **)(*hd2));
	(*hd) = ft_strsplit(obj_data[3], ' ');
	error_if_not(*hd, 1);
}

void		parse_cyl(t_gl *gl, char **obj_data, int j)
{
	char	**hd;
	char	**hd2;
	t_3dpt	one;
	t_3dpt	two;
	double	a;

	error_if_not(obj_data, 7);
	gl->obj_data[j]->type = "cyl";
	hd = ft_strsplit(obj_data[1], ' ');
	hd2 = ft_strsplit(obj_data[5], ' ');
	error_if_not(hd, 3);
	error_if_not(hd2, 3);
	one = create_3dpt(ft_atod(hd[0]) + ft_atod(hd2[0]), ft_atod(hd[1]) +
ft_atod(hd2[1]), ft_atod(hd[2]) + ft_atod(hd2[2]));
	parse_cyl_2(&hd, &hd2, &two, obj_data);
	a = ft_atod(hd[0]);
	free_array((void **)hd);
	hd = ft_strsplit(obj_data[4], ' ');
	error_if_not(hd, 4);
	gl->obj_data[j]->obj = create_cyl(one, normal(two), a, create_color(
ft_atod(hd[0]), ft_atod(hd[1]), ft_atod(hd[2]), ft_atod(hd[3])));
	free_array((void **)hd);
}
