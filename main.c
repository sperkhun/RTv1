/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperkhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 17:20:22 by sperkhun          #+#    #+#             */
/*   Updated: 2018/02/28 17:34:27 by sperkhun         ###   ########.fr       */
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
    win = SDL_CreateWindow("Hello SDL World",\
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_W, WIN_H, SDL_WINDOW_ALLOW_HIGHDPI);
    if (NULL == win)
        exit (1);
    screen = SDL_GetWindowSurface(win);
    // scene.object = (t_object*)malloc(sizeof(t_object) * 4);
    // scene.light = (t_light*)malloc(sizeof(t_light) * 3);
    // scene.camera.ov = (t_vector){0, 0, 0};
    // scene.camera.rot = (t_vector){0, 0, 0};
    // scene.camera.d = 1;
    // scene.light[0].v = (t_vector){-4, 2, 1};
    // scene.light[0].intensity = 0.5;
    // scene.light[1].v = (t_vector){0, 0, 0};
    // scene.light[1].intensity = 0.1;
    // scene.light[2].v = (t_vector){10, 0.5, 3};
    // scene.light[2].intensity = 0.4;
    // scene.object[0].v = (t_vector){0, -9001, 0};
    // scene.object[0].r = 9000;
    // scene.object[0].specular = -1;
    // scene.object[0].col = (t_vector){0, 255, 0};
    // scene.object[0].type = "SPHERE";
    // scene.object[1].v = (t_vector){-1, 0.5, 5.0};
    // scene.object[1].r = 1;
    // scene.object[1].specular = 100;
    // scene.object[1].col = (t_vector){255, 0, 0};
    // scene.object[1].type = "SPHERE";
    // scene.object[2].v = (t_vector){1.5, 0, 6};
    // scene.object[2].r = 1;
    // scene.object[2].specular = 100;
    // scene.object[2].col = (t_vector){0, 0, 255};
    // scene.object[2].type = "CYLINDER";
    // scene.object[3].v = (t_vector){0, 0, 5};
    // scene.object[3].k = tan(M_PI / 6);
    // scene.object[3].specular = -1;
    // scene.object[3].col = (t_vector){255, 255, 0};
    // scene.object[3].type = "CONE";
    read_scene(&scene, argv[1]);
    ft_memset(screen->pixels, 0, screen->h * screen->pitch);
    draw(screen, scene);
    SDL_UpdateWindowSurface(win);
    while (running)
        while(SDL_PollEvent(&event))
        {
            if((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
                running = 0;
        }
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(win);
    SDL_Quit();
    system("leaks rtv1");
    return (0);
}

