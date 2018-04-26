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

t_vector traceray(t_scene scene)
{
	t_vector	p;
	t_vector	n;
	t_vector	color;
	double	i;
	int	a;
	double m;

	a = intersection(scene.object, scene.camera.ov, scene.camera.vv, 1, 10000, &scene.cl_t);
	if (a < 0)
		return ((t_vector){0, 0, 0});
	p = scene.camera.ov + MULT(scene.camera.vv, scene.cl_t);
	if (!ft_strcmp(scene.object[a].type, "SPHERE"))
		n = p - scene.object[a].v;
	else if (!ft_strcmp(scene.object[a].type, "CYLINDER"))
	{
		m = SCALAR(scene.camera.vv, ((t_vector){0, 1, 0})) * scene.cl_t + SCALAR(scene.camera.ov - scene.object[a].v, ((t_vector){0, 1, 0}));
		n = p - scene.object[a].v - MULT(((t_vector){0, 1, 0}), m);
	}
	else
	{
		m = SCALAR(scene.camera.vv, ((t_vector){0, 1, 0})) * scene.cl_t + SCALAR(scene.camera.ov - scene.object[a].v, ((t_vector){0, 1, 0}));
		n = p - scene.object[a].v - MULT(((t_vector){0, 1, 0}), (m * (1 + pow(scene.object[a].k, 2))));
	}
	n = DIV(n, LENGTH(n));
	i = lighting(p, n, -scene.camera.vv, scene, scene.object[a]);
	color = MULT(scene.object[a].col, i);
	return (color);
}