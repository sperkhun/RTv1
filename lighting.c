/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 16:05:19 by sperkhun          #+#    #+#             */
/*   Updated: 2018/04/26 16:05:20 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	lighting(t_vector p, t_vector n, t_vector v, t_scene scene, t_object object)
{
	t_vector l;
	t_vector r;
	double	i;
	double	n_l;
	double	r_v;
	int a;
	int b;

	i = 0.0;
	a = 0;
	while (a < 4)
	{
		l = scene.light[a].v - p;
		n_l = (n * l)[0] + (n * l)[1] + (n * l)[2];
		b = intersection(scene.object, p, l, 0.001, 1, &scene.cl_t);
		if (b >= 0)
		{
			a++;
			continue ;
		}
		if (n_l > 0)
			i += scene.light[a].intensity * n_l / (LENGTH(n) * LENGTH(l));
		if (object.specular != -1)
		{
			r = MULT(n, 2 * SCALAR(n, l)) - l;
			r_v = SCALAR(r, v);
			if (r_v > 0)
			{
				i += scene.light[a].intensity * pow(r_v / (LENGTH(r) * LENGTH(v)), object.specular);
			}
		}
		a++;
	}
	return (i);
}
