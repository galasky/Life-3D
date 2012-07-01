/*
** life.h for life in /home/teisse_l/Document/projet/life
** 
** Made by lambert teisserenc-bonesteve
** Login   <teisse_l@epitech.net>
** 
** Started on  Sun May  6 01:52:12 2012 lambert teisserenc-bonesteve
** Last update Sun May  6 10:28:15 2012 lambert teisserenc-bonesteve
*/

#include <fmodex/fmod.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#ifndef	__LIFE_H__
#define	__LIFE_H__

typedef struct  s_img
{
  int           bpp;
  int           sizeline;
  int           endian;
}               t_img;

typedef struct	s_rt
{
  int		tf;
  int		tp;
  int		s;
  int		max;
  int		cycle;
  int		**tab;
  int		**cpy;
  SDL_Surface	*ecran;
  SDL_Surface	*run;
  SDL_Rect	p_run;
  SDL_Surface   *pixel;
  SDL_Rect      p_p;
  SDL_Event     event;
}		t_rt;

/*		put_life	*/
void		aff_tab(t_rt *rt);


/*		run		*/
void		run(t_rt *rt);

/*		main		*/
void		*xmalloc(int size);

#endif
