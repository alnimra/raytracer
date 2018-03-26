/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:13:02 by mray              #+#    #+#             */
/*   Updated: 2018/03/16 17:13:02 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	*create_obj(void *obj, char *type)
{
	t_obj *tmp;

	tmp = (t_obj *)malloc(sizeof(t_obj));
	tmp->obj = obj;
	tmp->type = type;
	return (tmp);
}
