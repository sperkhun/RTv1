/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/02 11:13:37 by sperkhun          #+#    #+#             */
/*   Updated: 2018/03/02 11:13:38 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H

# define RTV1_H

# include "libft.h"
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <SDL.h>

# define WIN_H 800

# define WIN_W 1000

typedef double	t_vector __attribute__((vector_size(sizeof(double)*3)));

typedef struct  s_sphere
{
	t_vector v;
	double r;
	t_vector col;
}				t_sphere;

typedef struct  s_camera
{
	t_vector ov;
	t_vector vv;
	double d;
}				t_camera;

typedef struct  s_light
{
	t_vector v;
	double intensity;
}				t_light;

#endif
