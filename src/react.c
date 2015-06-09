/*
** react.c for show_text_input in /home/pirez_l/Documents/3ds/show_text_input
** 
** Made by Loïc Pirez
** Login   <loic.pirez@epitech.eu>
** 
** Started on  Wed Apr 22 22:33:31 2015 Loïc Pirez
** Last update Thu Apr 23 18:04:03 2015 Loïc Pirez
*/

#include "../include/color.h"
#include "../include/react.h"
#include "../include/my.h"
#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void
clean(void) {
  exitCfgu();
  gfxExit();
  hidExit();
  aptExit();
  srvExit();
  exit (0);
}

void
init(void) {
  srvInit();		   // services
  aptInit();		   // applets
  hidInit(NULL);	   // input
  gfxInitDefault();        // graphics
  initCfgu();		   // Use for show the printf
  gfxSet3D(false);	   // stereoscopy (true == on / false == off)
  consoleInit(GFX_BOTTOM, 0);
}

void
react_to_input(void) {
  u32 kDown;

  kDown = hidKeysDown();

  if (kDown & KEY_SELECT)
    printf(MAGENTA "Select\n" RESET);
  if (kDown & KEY_START)
    clean();

  if (kDown & KEY_CPAD_UP)
    printf(RED "CUp\n" RESET);
  if (kDown & KEY_CPAD_RIGHT)
    printf(GREEN "CRight\n" RESET);
  if (kDown & KEY_CPAD_LEFT)
    printf(YELLOW "CLeft\n" RESET);
  if (kDown & KEY_CPAD_DOWN)
    printf(RED "CDown\n" RESET);

  if (kDown & KEY_DUP)
    printf(RED "DUp\n" RESET);
  if (kDown & KEY_DRIGHT)
    printf(GREEN "DRight\n" RESET);
  if (kDown & KEY_DLEFT)
    printf(YELLOW "DLeft\n" RESET);
  if (kDown & KEY_DDOWN)
    printf(RED "DDown\n" RESET);

  if (kDown & KEY_Y)
    printf(CYAN "Y\n" RESET);
  if (kDown & KEY_X)
    printf(WHITE "X\n" RESET);
  if (kDown & KEY_A)
    printf(MAGENTA "A\n" RESET);
  if (kDown & KEY_B)
    printf(YELLOW "B\n" RESET);

  if (kDown & KEY_L)
    printf(BLUE "L\n" RESET);
  if (kDown & KEY_R)
    printf(RED "R\n" RESET);

  //New3DS
  if (kDown & KEY_CSTICK_UP)
    printf(RED "CStickUp\n" RESET);
  if (kDown & KEY_CSTICK_RIGHT)
    printf(GREEN "CStickRight\n" RESET);
  if (kDown & KEY_CSTICK_LEFT)
    printf(YELLOW "CStickLeft\n" RESET);
  if (kDown & KEY_CSTICK_DOWN)
    printf(RED "CStickDown\n" RESET);

  if (kDown & KEY_ZL)
    printf(BLUE "ZL\n" RESET);
  if (kDown & KEY_ZR)
    printf(RED "ZR\n" RESET);
}
