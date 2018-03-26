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

void	errorify(char *str)
{
	ft_putstr(str);
	exit(1);
}

char	*read_in(char *filename)
{
	int		fd;
	int		byte_size;
	char	*str;
	char	*line;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		errorify("File opening error");
	str = ft_strdup("");
	line = NULL;
	while ((byte_size = get_next_line(fd, &line) > 0))
	{
		tmp = line;
		line = ft_strjoin(line, "\n");
		ft_memdel((void **)&tmp);
		tmp = str;
		str = ft_strjoin(str, line);
		ft_memdel((void **)&tmp);
		if (line)
			ft_memdel((void **)&line);
	}
	if (line)
		ft_memdel((void **)&line);
	return (str);
}

void	add_to_overall_obj_data(t_gl *gl, char **obj_data, int j)
{
	if (ft_strcmp(obj_data[0], "cam") == 0)
		gl->cam_count++;
	if (ft_strcmp(obj_data[0], "light") == 0)
		gl->light_count++;
	gl->obj_data[j] = (t_obj *)malloc(sizeof(t_obj));
	if (ft_strcmp(obj_data[0], "sphere") == 0)
		parse_sphere(gl, &obj_data, j);
	else if (ft_strcmp(obj_data[0], "cyl") == 0)
		parse_cyl(gl, obj_data, j);
	else if (ft_strcmp(obj_data[0], "cone") == 0)
		parse_cone(gl, obj_data, j);
	else if (ft_strcmp(obj_data[0], "plane") == 0)
		parse_plane(gl, obj_data, j);
	else if (ft_strcmp(obj_data[0], "light") == 0)
		parse_light(gl, obj_data, j);
	else if (ft_strcmp(obj_data[0], "cam") == 0)
		parse_cam(gl, obj_data, j);
	else
		errorify("Not a validi file");
}

int		get_num_of_objs(char **obj_string_data_total)
{
	int j;

	j = 0;
	while (obj_string_data_total[j])
		j++;
	return (j);
}

void	parse_obj_data(t_gl *gl, char *data)
{
	char	**object_string_data_total;
	char	**obj_data;
	int		i;

	object_string_data_total = ft_strsplit(data, '\n');
	gl->cam_count = 0;
	gl->light_count = 0;
	gl->obj_data = ft_memalloc(sizeof(t_obj *) *
							(get_num_of_objs(object_string_data_total) + 1));
	ft_putnbr(get_num_of_objs(object_string_data_total));
	i = 0;
	while (object_string_data_total[i])
	{
		obj_data = ft_strsplit(object_string_data_total[i], '|');
		ft_putendl(obj_data[0]);
		add_to_overall_obj_data(gl, obj_data, i);
		free_array((void **)obj_data);
		i++;
	}
	if (gl->cam_count != 1)
		errorify("No cams man.");
	if (gl->light_count <= 0)
		errorify("How are you going to see if you don't add lights...");
	free_array((void **)object_string_data_total);
	free(data);
}
