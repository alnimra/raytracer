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

t_vec	*create_vec(t_3dpt org, t_3dpt dir)
{
	t_vec *tmp;

	tmp = (t_vec *)malloc(sizeof(t_vec));
	tmp->comp[0] = org;
	tmp->comp[1] = dir;
	return (tmp);
}

void	set_vec(t_vec *v, t_3dpt org, t_3dpt dir)
{
	v->comp[0] = org;
	v->comp[1] = dir;
}
