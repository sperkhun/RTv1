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
	t_vector	l;
	double		i;
	double		n_l;
	int			a;

	i = 0.0;
	a = 0;
	while (a < scene.l)
	{
		l = scene.light[a].v - p;
		n_l = (n * l)[0] + (n * l)[1] + (n * l)[2];
		if (intersection(&scene, p, l, 0.001, 1) >= 0)
		{
			a++;
			continue ;
		}
		if (n_l > 0)
			i += scene.light[a].intensity * n_l / (LENGTH(n) * LENGTH(l));
		if (object.specular != -1)
		{
			l = MULT(n, 2 * SCALAR(n, l)) - l;
			n_l = SCALAR(l, v);
			n_l > 0 ? i += scene.light[a].intensity * pow(n_l / (LENGTH(l) *\
				LENGTH(v)), object.specular) : 0;
		}
		a++;
	}
	return (i);
}
