/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:02:59 by sperkhun          #+#    #+#             */
/*   Updated: 2018/04/26 16:03:00 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector	traceray(t_scene scene)
{
	t_vector	p;
	t_vector	n;
	double		i;
	int			a;

	scene.t_min = 1;
	scene.t_max = 10000;
	if ((a = intersection(&scene, scene.camera.ov, scene.camera.vv)) < 0)
		return ((t_vector){0, 0, 0});
	p = scene.camera.ov + MULT(scene.camera.vv, scene.cl_t);
	i = (SCALAR(scene.camera.vv, scene.object[a].rot) * scene.cl_t) +\
			SCALAR((scene.camera.ov - scene.object[a].v), scene.object[a].rot);
	if (!ft_strcmp(scene.object[a].type, "PLANE"))
		n = SCALAR(scene.camera.vv, scene.object[a].rot) < 0 ?\
				scene.object[a].rot : -scene.object[a].rot;
	if (!ft_strcmp(scene.object[a].type, "SPHERE"))
		n = p - scene.object[a].v;
	if (!ft_strcmp(scene.object[a].type, "CYLINDER"))
		n = p - scene.object[a].v - MULT(scene.object[a].rot, i);
	if (!ft_strcmp(scene.object[a].type, "CONE"))
		n = p - scene.object[a].v - MULT(scene.object[a].rot, (i *\
			(1 + pow(scene.object[a].r, 2))));
	n = DIV(n, LENGTH(n));
	i = lighting(p, n, scene, scene.object[a]);
	return (MULT(scene.object[a].col, i));
}
