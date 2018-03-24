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

t_cam *create_cam(t_3dpt org, t_3dpt dir, t_3dpt right, t_3dpt down)
{
    t_cam *tmp;

    tmp = (t_cam *)malloc(sizeof(t_cam));
    tmp->prop[0] = org;
    tmp->prop[1] = dir;
    tmp->prop[2] = right;
    tmp->prop[3] = down;
    return (tmp);
}
