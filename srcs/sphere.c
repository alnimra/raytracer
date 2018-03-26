/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 20:35:13 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 20:35:13 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		find_intersection_sphere(t_sphere *sphere, t_vec *vec)
{
	double coef[3];

	coef[0] = pow(vec->comp[1][0], 2) + pow(vec->comp[1][1], 2) +
		pow(vec->comp[1][2], 2);
	coef[1] = (2 * (vec->comp[0][0] - sphere->cnt[0]) * vec->comp[1][0]) +
		(2 * (vec->comp[0][1] - sphere->cnt[1]) * vec->comp[1][1]) +
		(2 * (vec->comp[0][2] - sphere->cnt[2]) * vec->comp[1][2]);
	coef[2] = pow(vec->comp[0][0] - sphere->cnt[0], 2) +
		pow(vec->comp[0][1] - sphere->cnt[1], 2) +
		pow(vec->comp[0][2] - sphere->cnt[2], 2) - (sphere->rad * sphere->rad);
	return (solve_for_roots(coef));
}

t_sphere	*create_sphere(t_3dpt cnt, double rad, t_color col)
{
	t_sphere *tmp;

	tmp = (t_sphere *)malloc(sizeof(t_sphere));
	tmp->cnt = cnt;
	tmp->rad = rad;
	tmp->col = col;
	tmp->find_insct = find_intersection_sphere;
	return (tmp);
}

t_3dpt		sphere_get_normal_at(t_sphere *sphere, t_3dpt pt)
{
	t_3dpt ret;

	ret = normal(add(pt, (multi(sphere->cnt, -1))));
	return (ret);
}

void		parse_sphere_2(char ***hd, char ***hd2, char ***obj_data, double *a)
{
	free_array((void **)(*hd));
	free_array((void **)(*hd2));
	(*hd) = ft_strsplit((*obj_data)[2], ' ');
	error_if_not(*hd, 1);
	*a = ft_atod((*hd)[0]);
	free_array((void **)(*hd));
	(*hd) = ft_strsplit((*obj_data)[3], ' ');
	error_if_not(*hd, 4);
}

void		parse_sphere(t_gl *gl, char ***obj_data, int j)
{
	char	**hd;
	char	**hd2;
	t_3dpt	one;
	double	a;

	error_if_not(*obj_data, 6);
	gl->obj_data[j]->type = "sphere";
	hd = ft_strsplit((*obj_data)[1], ' ');
	hd2 = ft_strsplit((*obj_data)[4], ' ');
	error_if_not(hd, 3);
	error_if_not(hd2, 3);
	one = create_3dpt(ft_atod(hd[0]) + ft_atod(hd2[0]),
					ft_atod(hd[1]) + ft_atod(hd2[1]),
					ft_atod(hd[2]) + ft_atod(hd2[2]));
	parse_sphere_2(&hd, &hd2, obj_data, &a);
	gl->obj_data[j]->obj =
		create_sphere(one, a,
				create_color(ft_atod(hd[0]), ft_atod(hd[1]),
						ft_atod(hd[2]), ft_atod(hd[3])));
	free_array((void **)hd);
}
