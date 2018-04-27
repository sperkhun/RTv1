/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:20:22 by sperkhun          #+#    #+#             */
/*   Updated: 2018/04/27 17:44:11 by sperkhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int main(int argc, char **argv)
{
	int running = 1;
	SDL_Event event;
	SDL_Window *win;
	SDL_Surface *screen;
	t_scene scene;

	if (argc != 2)
		return (0);
	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("Hello SDL World", SDL_WINDOWPOS_UNDEFINED,\
			SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI);
	if (NULL == win)
		exit(1);
	screen = SDL_GetWindowSurface(win);
	read_scene(&scene, argv[1]);
	ft_memset(screen->pixels, 0, screen->h * screen->pitch);
	draw(screen, scene);
	SDL_UpdateWindowSurface(win);
	while (running)
		while (SDL_PollEvent(&event))
		{
			if ((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type &&\
					SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
				running = 0;
		}
	SDL_FreeSurface(screen);
	SDL_DestroyWindow(win);
	SDL_Quit();
	system("leaks rtv1");
	return (0);
}
