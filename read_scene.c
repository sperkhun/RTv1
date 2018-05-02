/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:46:43 by sperkhun          #+#    #+#             */
/*   Updated: 2018/04/26 16:46:44 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		count_objects(char *str, t_scene *scene)
{
	int		fd;
	char	*line;

	fd = open(str, O_RDONLY);
	scene->l = 0;
	scene->o = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strncmp(line, "LIGHT", 5))
			scene->l++;
		if (!ft_strncmp(line, "PLANE", 5) || !ft_strncmp(line, "SPHERE", 6) ||\
			!ft_strncmp(line, "CYLINDER", 8) || !ft_strncmp(line, "CONE", 4))
			scene->o++;
		free(line);
	}
	free(line);
	scene->light = (t_light*)malloc(sizeof(t_light) * scene->l);
	scene->object = (t_object*)malloc(sizeof(t_object) * scene->o);
	close(fd);
}

static t_vector	read_vector(char *str, int s)
{
	t_vector	v;
	int			i;

	i = 0;
	str = ft_strchr(str, '{');
	str++;
	while (i < 3)
	{
		v[i] = (double)ft_atoi(str);
		!s ? v[i] /= 10 : 0;
		str = ft_strchr(str, ',');
		str++;
		i++;
	}
	return (v);
}

static void		read_light(t_light *light, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (i < 2)
	{
		get_next_line(fd, &line);
		if (i == 0)
			light->intensity = (double)ft_atoi(line) / 10;
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

	i = 0;
	while (i < 5)
	{
		if (i == 4 && !ft_strcmp(object->type, "SPHERE"))
			break ;
		if (i == 1 && !ft_strcmp(object->type, "PLANE"))
		{
			i++;
			continue ;
		}
		get_next_line(fd, &line);
		if (i == 0)
			object->specular = ft_atoi(line);
		if (i == 1)
			object->r = (double)ft_atoi(line) / 10;
		if (i == 2)
			object->v = read_vector(line, 0);
		if (i == 3)
			object->col = read_vector(line, 1);
		if (i == 4)
		{
			object->rot = read_vector(line, 0);
			object->rot = DIV(object->rot, LENGTH(object->rot));
		}
		i++;
		free(line);
	}
}

void			read_camera(t_camera *camera, int fd)
{
	char	*line;
	int		i;

	i = 0;
	camera->d = 1;
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

void			read_scene(t_scene *scene, char *str)
{
	int		fd;
	int		l;
	int		o;
	char	*line;
	char	*s;

	count_objects(str, scene);
	fd = open(str, O_RDONLY);
	o = 0;
	l = 0;
	scene->shadows = 0;
	while (get_next_line(fd, &line) > 0)
	{
		s = ft_strtrim(line);
		if (!ft_strcmp(s, "SHADOWS"))
		{
			free(s);
			scene->shadows = 1;
		}
		else if (!ft_strcmp(s, "LIGHT"))
		{
			read_light(&scene->light[l], fd);
			free(s);
			l++;
		}
		else if (!ft_strcmp(s, "CYLINDER") || !ft_strcmp(s, "CONE") ||\
			!ft_strcmp(s, "SPHERE") || !ft_strcmp(s, "PLANE"))
		{
			scene->object[o].type = s;
			read_obj(&scene->object[o], fd);
			o++;
		}
		else if (!ft_strcmp(s, "CAMERA") && l == 0 && o == 0)
		{
			read_camera(&scene->camera, fd);
			free(s);
		}
		else
			exit(0);
		free(line);
	}
	free(line);
	close(fd);
}
