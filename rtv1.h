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

# define SCALAR(v1, v2) ((v1 * v2)[0] + (v1 * v2)[1] + (v1 * v2)[2])

# define LENGTH(v) sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])

# define MULT(v, n) v * (t_vector){n, n, n}

# define DIV(v, n) n ? v / (t_vector){n, n, n} : (t_vector){0, 0, 0}

# define NORM(v) DIV(v, LENGTH(v))

typedef double	t_vector __attribute__((vector_size(sizeof(double)*3)));

typedef struct	s_object
{
	t_vector	v;
	t_vector	col;
	t_vector	rot;
	double		r;
	double		specular;
	double		t1;
	double		t2;
	char		*type;
}				t_object;

typedef struct	s_camera
{
	t_vector	ov;
	t_vector	vv;
	t_vector	rot;
	double		d;
}				t_camera;

typedef struct	s_light
{
	t_vector	v;
	double		intensity;
}				t_light;

typedef struct	s_scene
{
	SDL_Event	event;
	SDL_Window	*win;
	SDL_Surface	*screen;
	t_camera	camera;
	t_light		*light;
	t_object	*object;
	double		cl_t;
	double		t_min;
	double		t_max;
	int			shadows;
	int			l;
	int			o;
}				t_scene;

void			open_window(t_scene *scene);
void			draw(SDL_Surface *screen, t_scene scene);
t_vector		traceray(t_scene scene);
double			lighting(t_vector p, t_vector n, t_scene scene,\
							t_object object);
int				intersection(t_scene *scene, t_vector o, t_vector v);
void			read_scene(t_scene *scene, char *str);
void			read_light(t_light *light, int fd);
void			read_obj(t_object *object, int fd);
void			read_camera(t_camera *camera, int fd);
void			iserr(char *str, int i);

#endif
