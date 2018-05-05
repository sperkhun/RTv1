/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:07:35 by sperkhun          #+#    #+#             */
/*   Updated: 2018/05/03 13:07:36 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double	ft_atof(char *s)
{
	double	i;
	int		a;
	int		l;

	i = ft_atoi(s);
	a = -1;
	l = 1;
	while (ft_isspace(*s))
		s++;
	if (*s == '+' || *s == '-')
	{
		l = *s == '-' && !i ? -1 : 1;
		s++;
	}
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
		s++;
	while (ft_isdigit(*s))
	{
		i += (*s - 48) * pow(10, a);
		s++;
		a--;
	}
	return (i * l);
}

static t_vector	read_vector(char *string, int s)
{
	t_vector	v;
	char		*str;
	int			i;

	i = 0;
	if (!(str = ft_strchr(string, '{')))
		iserr(ft_strjoin("Wrong vector: ", string), 1);
	str++;
	while (i < 3)
	{
		!*str ? iserr(ft_strjoin("Wrong vector: ", string), 1) : 0;
		v[i] = !s ? ft_atof(str) : ft_atoi(str);
		if (!(str = ft_strchr(str, ',')) && i < 2)
			iserr(ft_strjoin("Wrong vector: ", string), 1);
		str++;
		i++;
	}
	return (v);
}

void			read_light(t_light *light, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 2)
	{
		get_next_line(fd, &line);
		if (i == 0)
			light->intensity = ft_atof(line);
		else if (i == 1)
			light->v = read_vector(line, 0);
		i++;
		free(line);
	}
}

void			read_obj(t_object *object, int fd)
{
	char	*line;
	int		i;

	i = -1;
	while (++i < 5)
	{
		if (i == 4 && !ft_strcmp(object->type, "SPHERE"))
			break ;
		if (i == 1 && !ft_strcmp(object->type, "PLANE"))
			i++;
		get_next_line(fd, &line);
		if (i == 0)
			object->specular = ft_atoi(line);
		if (i == 1)
			(object->r = ft_atof(line)) >= 3.14 &&\
				!ft_strcmp(object->type, "CONE") ? iserr("Wrong cone", 1) : 0;
		if (i == 2)
			object->v = read_vector(line, 0);
		if (i == 3)
			object->col = read_vector(line, 1);
		if (i == 4)
			object->rot = NORM(read_vector(line, 0));
		i == 4 && !(LENGTH(object->rot)) ? iserr("Wrong axis vector", 1) : 0;
		free(line);
	}
}

void			read_camera(t_camera *camera, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 2)
	{
		get_next_line(fd, &line);
		if (i == 0)
			camera->ov = read_vector(line, 0);
		if (i == 1)
			camera->rot = read_vector(line, 0);
		i++;
		free(line);
	}
}
