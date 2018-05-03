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

static void	count_objects(char *str, t_scene *scene)
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

static int	check_objects(t_scene *scene, int fd, int *l, int *o)
{
	int		n;
	char	*line;

	if ((n = get_next_line(fd, &line)) > 0)
	{
		if (!ft_strncmp(line, "SHADOWS", 6))
			scene->shadows = 1;
		else if (!ft_strncmp(line, "LIGHT", 5))
			read_light(&scene->light[(*l)++], fd);
		else if (!ft_strncmp(line, "CYLINDER", 8) ||\
				!ft_strncmp(line, "CONE", 4) || !ft_strncmp(line, "SPHERE", 6)\
				|| !ft_strncmp(line, "PLANE", 5))
		{
			scene->object[*o].type = line;
			read_obj(&scene->object[(*o)++], fd);
		}
		else if (!ft_strncmp(line, "CAMERA", 6) && *l == 0 && *o == 0)
			read_camera(&scene->camera, fd);
		else
			iserr(ft_strjoin("Wrong object: ", line));
		!ft_strncmp(line, "SHADOWS", 6) || !ft_strncmp(line, "LIGHT", 5) ||\
					!ft_strncmp(line, "CAMERA", 6) ? free(line) : 0;
	}
	n == 0 ? free(line) : 0;
	return (n);
}

void		read_scene(t_scene *scene, char *str)
{
	int		fd;
	int		l;
	int		o;

	count_objects(str, scene);
	fd = open(str, O_RDONLY);
	o = 0;
	l = 0;
	scene->shadows = 0;
	while (check_objects(scene, fd, &l, &o) > 0)
		;
	close(fd);
}

void		iserr(char *str)
{
	ft_putendl(str);
	system("leaks rtv1");
	exit(0);
}
