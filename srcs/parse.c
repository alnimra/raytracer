/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mray <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 12:57:38 by mray              #+#    #+#             */
/*   Updated: 2018/03/18 12:57:38 by mray             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>
void errorify(char *str)
{
	ft_putstr(str);
	exit(1);
}

char *read_in(char *filename)
{
	int   fd;
	int   byte_size;
	char  buf[BUFF_SIZE + 1];
	char *str;
	char *tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		errorify("File opening error");
	str = ft_strnew(1);
	while ((byte_size = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[BUFF_SIZE] = '\0';
		tmp = str;
		str = ft_strjoin(str, buf);
		if (tmp)
			free(tmp);
	}
	return str;
}

void add_to_overall_obj_data(t_gl *gl, char **obj_data, int j)
{
	char ** held_data;
	char ** held_data2;
	t_3dpt *one;
	double  a;

	one = NULL;
	gl->obj_data[j] = (t_obj *)malloc(sizeof(t_obj));
	if (ft_strcmp(obj_data[0], "sphere") == 0)
	{
		if (!obj_data[5])
			errorify("Not a valid file");
		gl->obj_data[j]->type = "sphere";
		(gl->obj_data[j]->obj) = (t_sphere *)malloc(sizeof(t_sphere));
		held_data = ft_strsplit(obj_data[1], ' ');
		held_data2 = ft_strsplit(obj_data[4], ' ');
		if (!held_data[2] || !held_data2[2])
			errorify("Not a valid file");
		one = create_3dpt(ft_atod(held_data[0]) + ft_atod(held_data2[0]),
						  ft_atod(held_data[1]) + ft_atod(held_data2[1]),
						  ft_atod(held_data[2]) + ft_atod(held_data2[2]));
		free_array((void **)held_data);
		free_array((void **)held_data2);
		held_data = ft_strsplit(obj_data[2], ' ');
		if (!held_data[0])
			errorify("Not a valid file");
		a = ft_atod(held_data[0]);
		free_array((void **)held_data);
		held_data = ft_strsplit(obj_data[3], ' ');
		if (!held_data[3])
			errorify(" a valid file");
		gl->obj_data[j]->obj = create_sphere(
			one, a,
			create_color(ft_atod(held_data[0]), ft_atod(held_data[1]),
						 ft_atod(held_data[2]), ft_atod(held_data[3])));
		free_array((void **)held_data);
	}
	else if (ft_strcmp(obj_data[0], "plane") == 0)
	{
		if (!obj_data[3])
			errorify("Not a valid file");
		gl->obj_data[j]->type = "plane";
		(gl->obj_data[j]->obj) = (t_plane *)malloc(sizeof(t_plane));
		held_data = ft_strsplit(obj_data[1], ' ');
		if (!held_data[2])
			errorify("Not a valid file");
		one = create_3dpt(ft_atod(held_data[0]), ft_atod(held_data[1]),
						  ft_atod(held_data[2]));
		free_array((void **)held_data);
		held_data = ft_strsplit(obj_data[2], ' ');
		if (!held_data[0])
			errorify("Not a valid file");
		a = ft_atod(held_data[0]);
		free_array((void **)held_data);
		held_data = ft_strsplit(obj_data[3], ' ');
		if (!held_data[3])
			errorify(" a valid file");
		gl->obj_data[j]->obj = create_plane(
			one, a,
			create_color(ft_atod(held_data[0]), ft_atod(held_data[1]),
						 ft_atod(held_data[2]), ft_atod(held_data[3])));
		free_array((void **)held_data);
	}
	else if (ft_strcmp(obj_data[0], "light") == 0)
	{
		if (!obj_data[2])
			errorify("Not a valid file");
		gl->obj_data[j]->type = "light";
		(gl->obj_data[j]->obj) = (t_light *)malloc(sizeof(t_light));
		held_data = ft_strsplit(obj_data[1], ' ');
		if (!held_data[2])
			errorify("Not a valid file");
		((t_light *)(gl->obj_data[j]->obj))->org =
			create_3dpt(ft_atod(held_data[0]), ft_atod(held_data[1]),
						ft_atod(held_data[2]));
		free_array((void **)held_data);
		held_data = ft_strsplit(obj_data[2], ' ');
		if (!held_data[3])
			errorify("Not a valid file");
		((t_light *)(gl->obj_data[j]->obj))->col =
			create_color(ft_atod(held_data[0]), ft_atod(held_data[1]),
						 ft_atod(held_data[2]), ft_atod(held_data[3]));
		free_array((void **)held_data);
	}
	else if (ft_strcmp(obj_data[0], "cam") == 0)
	{
		if (!obj_data[2])
			errorify("Not a valid file");
		gl->obj_data[j]->type = "cam";
		(gl->obj_data[j]->obj) = (t_cam *)malloc(sizeof(t_cam));
		held_data = ft_strsplit(obj_data[1], ' ');
		if (!held_data[2])
			errorify("Not a valid file");
		((t_cam *)(gl->obj_data[j]->obj))->prop[0] =
			create_3dpt(ft_atod(held_data[0]), ft_atod(held_data[1]),
						ft_atod(held_data[2]));
		free_array((void **)held_data);
		held_data = ft_strsplit(obj_data[2], ' ');
		if (!held_data[2])
			errorify("Not a valid file");
		((t_cam *)(gl->obj_data[j]->obj))->prop[1] =
			create_3dpt(ft_atoi(held_data[0]), ft_atoi(held_data[1]),
						ft_atoi(held_data[2]));
		free_array((void **)held_data);
	}
	else
		errorify("Not a validi file");
}

int get_num_of_objs(char **obj_string_data_total)
{
	int j;

	j = 0;
	while (obj_string_data_total[j])
		j++;
	return (j);
}

void parse_obj_data(t_gl *gl, char *data)
{
	char **object_string_data_total;
	char **obj_data;
	int	i;

	object_string_data_total = ft_strsplit(data, '\n');
	i = 0;
	gl->obj_data =
		ft_memalloc(sizeof(t_obj *) * get_num_of_objs(object_string_data_total));
	ft_putnbr(get_num_of_objs(object_string_data_total));
	i = 0;
	while (object_string_data_total[i + 1])
	{
		obj_data = ft_strsplit(object_string_data_total[i], '|');
		ft_putendl(obj_data[0]);
		add_to_overall_obj_data(gl, obj_data, i);
		free_array((void **)obj_data);
		i++;
	}
	// printf((t_plane*)gl->obj_data[1]->obj)->normal->coord[0];
	free_array((void **)object_string_data_total);
}
