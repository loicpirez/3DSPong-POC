/*
** my.h for raytracer in /home/parsy_a/Desktop/Rush/include
** 
** Made by lucas parsy
** Login   <parsy_a@epitech.net>
** 
** Started on  Fri Jan  2 20:37:44 2015 lucas parsy
** Last update Thu Apr 23 17:42:04 2015 Loïc Pirez
*/
#ifndef MY_H_
# define MY_H_
# define HOR 0
# define VERT 1
# include <3ds.h>
# include "struct_graph.h"

void gfxDrawSprite(gfxScreen_t screen, gfx3dSide_t side, const u8*
		   spriteData, u16 width, u16 height, s16 x, s16 y);
void	start_match(t_all *a);
int	main(int ac, char **av);
void    draw_objetcs(t_all *a);
void    chek_keys(t_all *a);
t_all   *alloc_struct();
void	clean(void);
void	react_to_input(void);

#endif /*MY_H_*/
