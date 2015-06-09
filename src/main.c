/*
** main.c for pong in /home/pirez_l/Documents/3ds/3dsfun/pong
** 
** Made by Loïc Pirez
** Login   <loic.pirez@epitech.eu>
** 
** Started on  Thu Apr 23 17:33:34 2015 Loïc Pirez
** Last update Sat Apr 25 16:24:38 2015 Loïc Pirez
*/

#include "../include/color.h"
#include "../include/my.h"
#include "../include/react.h"
#include "../include/struct_graph.h"
#include "rect_bin.h"
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_all
*alloc_struct(void) {
  t_all *all;

  if ((all = malloc(sizeof(t_all))) == NULL)
    printf("Error : can't malloc.\n");

  all->pos_ball = malloc(sizeof(int) * 2);
  all->vect_ball = malloc(sizeof(int) * 2);
  all->score = malloc(sizeof(int) * 2);

  if (all->vect_ball == NULL || all->pos_ball == NULL || all->score == NULL)
    printf("Error: can't malloc.\n");

  all->sz_raq = 100;
  all->pos_ball[HOR] = 200;
  all->pos_ball[VERT] = 120;
  all->score[0] = 0;
  all->score[1] = 0;

 return (all);
}

int
check_keys(t_all *a) {
  u32	kHeld;
  u32	kDown;

  kHeld = hidKeysHeld();
  kDown = hidKeysDown();

  if (kDown & KEY_START)
    clean();
  if (((kDown | kHeld) & KEY_DOWN) && ((a->ra_l - 1) >= 0))
    a->ra_l -= 1;
  if (((kDown | kHeld) & KEY_B) && ((a->ra_r - 1) >= 0))
    a->ra_r -= 1;
  if (((kDown | kHeld) & KEY_UP) && ((a->ra_l + 1 + a->sz_raq)  <= 240))
    a->ra_l += 1;
  if (((kDown | kHeld) & KEY_X) && ((a->ra_r + 1 + a->sz_raq)  <= 240))
    a->ra_r += 1;

  return (1);
}

void
draw_objects(t_all *a) {
  u8* fb;

  fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

  memset(fb, 0, 240*400*3); // Cleaning the screen.

  gfxDrawSprite(GFX_TOP, GFX_LEFT, rect_bin, 20, a->sz_raq, 10, a->ra_l);
  gfxDrawSprite(GFX_TOP, GFX_LEFT, rect_bin, 20, a->sz_raq, 370, a->ra_r);
  gfxDrawSprite(GFX_TOP, GFX_LEFT, rect_bin, 20, 20,
		a->pos_ball[HOR], a->pos_ball[VERT]);
}

int
main(int ac, char **av) {
  t_all	*a;

  a = alloc_struct();

  start_match(a);
  init();
  while (aptMainLoop())
    {
      hidScanInput();
      if ((check_keys(a)) == -1)
	return (0);
      react_to_input();
      draw_objects(a);
      gfxFlushBuffers();
      gfxSwapBuffers();
      gspWaitForVBlank();
    }
  return (0);
}
