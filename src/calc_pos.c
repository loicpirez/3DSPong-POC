/*
** calc_pos.c for pong in /home/pirez_l/Documents/3ds/3dsfun/pong/src
** 
** Made by Loïc Pirez
** Login   <loic.pirez@epitech.eu>
** 
** Started on  Thu Apr 23 17:52:08 2015 Loïc Pirez
** Last update Thu Apr 23 17:53:43 2015 Loïc Pirez
*/

#include "../include/my.h"

void    start_match(t_all *a)
{
  a->ra_l = 120 - (a->sz_raq / 2);
  a->ra_l = 120 - (a->sz_raq / 2);
  a->pos_ball[HOR] = 120;
  a->pos_ball[VERT] = 200;
  a->vect_ball[HOR] = 1;
  a->vect_ball[VERT] = 0;
}
