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

void count_objects(char *str, int *l, int *o)
{
	int fd;
	char *line;

	fd = open(str, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strncmp(line, "LIGHT", 5))
			*l += 1;
		if (!ft_strncmp(line, "PLANE", 5) || !ft_strncmp(line, "SPHERE", 6) ||\
			!ft_strncmp(line, "CYLINDER", 8) || !ft_strncmp(line, "CONE", 4))
			*o += 1;
		free(line);
	}
	free(line);
	close(fd);
}

t_vector	read_vector(char *str, int s)
{
	t_vector v;
	int i;

	i = 0;
	str = !s ? ft_strchr(str, '{') : ft_strrchr(str, '{');
	str++;
	while (i < 3)
	{
		v[i] = (double)ft_atoi(str);
		str = ft_strchr(str, ',');
		str++;
		i++;
	}
	return (v);
}

void read_scene(t_scene *scene, char *str)
{
	int fd;
	int l;
	int o;
	char *line;
	char *s;

	count_objects(str, &scene->l, &scene->o);
	fd = open(str, O_RDONLY);
	o = 0;
	l = 0;
	scene->light = (t_light*)malloc(sizeof(t_light) * scene->l);
	scene->object = (t_object*)malloc(sizeof(t_object) * scene->o);
	while (get_next_line(fd, &line) > 0)
	{
		s = line;
		if (!ft_strncmp(line, "CAMERA", 6))
		{
			scene->camera.ov = read_vector(line, 0);
			scene->camera.rot = read_vector(line, 1);
			scene->camera.d = 1;
		}

		else if (!ft_strncmp(line, "SPHERE", 6))
		{
			scene->object[o].type = "SPHERE";
			line += 6;
			scene->object[o].specular = (double)ft_atoi(line);
			scene->object[o].v = read_vector(line, 0);
			scene->object[o].col = read_vector(line, 1);
			line = ft_strrchr(line, '}');
			line++;
			scene->object[o].r = (double)ft_atoi(line);
			o++;
		}
		else if (!ft_strncmp(line, "CYLINDER", 8))
		{
			scene->object[o].type = "CYLINDER";
			line += 8;
			scene->object[o].specular = (double)ft_atoi(line);
			scene->object[o].v = read_vector(line, 0);
			scene->object[o].col = read_vector(line, 1);
			line = ft_strrchr(line, '}');
			line++;
			scene->object[o].r = (double)ft_atoi(line);
			o++;
		}
		else if (!ft_strncmp(line, "CONE", 4))
		{
			scene->object[o].type = "CONE";
			line += 4;
			scene->object[o].specular = (double)ft_atoi(line);
			scene->object[o].v = read_vector(line, 0);
			scene->object[o].col = read_vector(line, 1);
			line = ft_strrchr(line, '}');
			line++;
			scene->object[o].k = (double)ft_atoi(line);
			o++;
		}
		else if (!ft_strncmp(line, "LIGHT", 5))
		{
			line += 5;
			scene->light[l].intensity = (double)ft_atoi(line) / 10;
			scene->light[l].v = read_vector(line, 0);
			l++;
		}
		free(s);
	}
	free(line);
	close(fd);
}
