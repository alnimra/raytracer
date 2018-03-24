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

double find_intersection_sphere(t_sphere *sphere, t_vec *vec)
{
    double a;
    double b;
    double c;
    double discriminant;
    double root_1;
    double root_2;
    a = pow(vec->comp[1][0], 2) + pow(vec->comp[1][1], 2) + pow(vec->comp[1][2], 2);
    b = (2 * (vec->comp[0][0] - sphere->cnt[0]) * vec->comp[1][0]) + (2 * (vec->comp[0][1] - sphere->cnt[1]) * vec->comp[1][1]) + (2 * (vec->comp[0][2] - sphere->cnt[2]) * vec->comp[1][2]);
    c = pow(vec->comp[0][0] - sphere->cnt[0], 2) + pow(vec->comp[0][1] - sphere->cnt[1], 2) + pow(vec->comp[0][2] - sphere->cnt[2], 2) - (sphere->rad * sphere->rad);
    discriminant = b * b - 4 * a * c;

    if(discriminant > 0)
    {
        root_1 = ((-1 * b - sqrt(discriminant)) / (2 * a)) - 0.000001;
        if(root_1 > 0)
            return (root_1);
        root_2 = ((sqrt(discriminant) - b) / (2 * a)) - 0.000001;
        return (root_2 > 0) ? (root_2) : -1;
    }
    return (-1);

}

t_sphere *create_sphere(t_3dpt cnt, double rad, t_color col)
{
    t_sphere *tmp;

    tmp = (t_sphere *)malloc(sizeof(t_sphere));
    tmp->cnt = cnt;
    tmp->rad = rad;
    tmp->col = col;
    tmp->find_insct = find_intersection_sphere;
    return (tmp);
}

t_3dpt sphere_get_normal_at(t_sphere *sphere, t_3dpt pt)
{
    t_3dpt ret;

    ret = normal(add(pt, (multi(sphere->cnt, -1))));
    return (ret);
}
