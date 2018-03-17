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

double find_intersection_plane(t_plane *plane, t_vec *vec)
{
    double a;
    double b;

    a = dot(plane->normal, vec->comp[1]);
    if (a == 0)
        return (-1);
    b = dot(plane->normal, multi(add(vec->comp[0], multi(plane->normal, plane->dist)), -1));
    return (-1 * (b / a));
}

t_plane *create_plane(t_3dpt *normal, double dist, t_color *col)
{
    t_plane *tmp;

    tmp = (t_plane *)malloc(sizeof(t_plane));
    tmp->normal = normal;
    tmp->dist = dist;
    tmp->col = col;
    tmp->find_insct = find_intersection_plane;
    return (tmp);
}