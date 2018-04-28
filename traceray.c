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
	t_vector	color;
	double		i;
	int			a;
	double		m;

	a = intersection(&scene, scene.camera.ov, scene.camera.vv, 1, 10000);
	if (a < 0)
		return ((t_vector){0, 0, 0});
	p = scene.camera.ov + MULT(scene.camera.vv, scene.cl_t);
	if (!ft_strcmp(scene.object[a].type, "SPHERE"))
	{
		n = p - scene.object[a].v;
	}
	else if (!ft_strcmp(scene.object[a].type, "CYLINDER"))
	{
		// m = (SCALAR(scene.camera.vv, scene.object[a].rot) * scene.cl_t) +\
			// SCALAR(scene.camera.ov - scene.object[a].v, scene.object[a].rot);
		m = sqrt(pow(LENGTH((p - scene.object[a].v)), 2) - pow(scene.object[a].r, 2));
		n = p - scene.object[a].v - MULT(scene.object[a].rot, m);

	}
	else
	{
		// m = SCALAR(scene.camera.vv, scene.object[a].rot) * scene.cl_t +\
		 	// SCALAR(scene.camera.ov - scene.object[a].v, scene.object[a].rot);
		m = cos(scene.object[a].r) * LENGTH((p - scene.object[a].v));
		n = p - scene.object[a].v - MULT(scene.object[a].rot, (m *\
			(1 + pow(scene.object[a].r, 2))));
	}
	n = DIV(n, LENGTH(n));
	i = lighting(p, n, -scene.camera.vv, scene, scene.object[a]);
	color = MULT(scene.object[a].col, i);
	if (!ft_strcmp(scene.object[a].type, "CYLINDER"))
	{
		printf("%f\n", SCALAR(n, scene.object[a].rot));
	}
	return (color);
}
