/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 19:26:19 by mray              #+#    #+#             */
/*   Updated: 2018/03/15 19:26:19 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_light *create_light(t_3dpt org, t_color col)
{
    t_light *tmp;

    tmp = (t_light *)malloc(sizeof(t_light));
    tmp->org = org;
    tmp->col = col;
    return (tmp);
}
