/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sandpt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 11:30:50 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 11:30:50 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_3dpt *create_3dpt(double x, double y, double z)
{
    t_3dpt *tmp;

    tmp = (t_3dpt *)malloc(sizeof(t_3dpt));
    tmp->coord[0] = x;
    tmp->coord[1] = y;
    tmp->coord[2] = z;
    return (tmp);
}

void    set3dpt(t_3dpt *pt, double x, double y, double z)
{
    pt->coord[0] = x;
    pt->coord[1] = y;
    pt->coord[2] = z;
}

double get_x(t_3dpt *pt)
{
    return (pt->coord[0]);
}

double get_y(t_3dpt *pt)
{
    return (pt->coord[1]);
}

double get_z(t_3dpt *pt)
{
    return (pt->coord[2]);
}
