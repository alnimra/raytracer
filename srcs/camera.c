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

t_cam *create_cam(t_3dpt *org, t_3dpt *dir, t_3dpt *right, t_3dpt *down)
{
    t_cam *tmp;

    tmp = (t_cam *)malloc(sizeof(t_cam));
    tmp->prop[0] = org;
    tmp->prop[1] = dir;
    tmp->prop[2] = right;
    tmp->prop[3] = down;
    return (tmp);
}

void    set_cam(t_cam *cam, double org_and_dir[3], double right[3], double down[3])
{
    set3dpt(cam->prop[0], org_and_dir[0], org_and_dir[1], org_and_dir[2]);
    set3dpt(cam->prop[1], org_and_dir[3], org_and_dir[4], org_and_dir[5]);
    set3dpt(cam->prop[2], right[0], right[1], right[2]);
    set3dpt(cam->prop[3], down[0], down[1], down[2]);
}

t_3dpt	*get_camorg(t_cam *cam)
{
    return (cam->prop[0]);
}

t_3dpt	*get_camdir(t_cam *cam)
{
    return (cam->prop[1]);
}

t_3dpt	*get_right(t_cam *cam)
{
    return (cam->prop[2]);
}

t_3dpt	*get_down(t_cam *cam)
{
    return (cam->prop[3]);
}