/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 12:00:21 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 12:00:21 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec *create_vec(t_3dpt *org, t_3dpt *dir)
{
    t_vec *tmp;

    tmp = (t_vec *)malloc(sizeof(t_vec));
    tmp->comp[0] = org;
    tmp->comp[1] = dir;
    return (tmp);
}

void    set_vec(t_vec *v, double org[3], double dir[3])
{
    set3dpt(v->comp[0], org[0], org[1], org[2]);
    set3dpt(v->comp[1], dir[0], dir[1], dir[2]);
}

t_3dpt	*get_org(t_vec *v)
{
    return (v->comp[0]);
}

t_3dpt	*get_dir(t_vec *v)
{
    return (v->comp[1]);
}