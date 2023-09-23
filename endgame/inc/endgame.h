#ifndef MYEZIK_ENDGAME_H
#define MYEZIK_ENDGAME_H

#include "collider.h"
#include "resourses.h"
#include "soldier.h"
#include "zombie.h"
#include "bullet.h"
#include "list.h"
#include "button.h"
#include "menu.h"
#include "levels.h"

void handle_event(SDL_Event *SDL_Event);
void one_game(SDL_Renderer *renderer);
void endgame(void);
#endif
