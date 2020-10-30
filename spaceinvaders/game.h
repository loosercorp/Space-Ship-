#pragma once
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/keyboard.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro5.h>
#include <allegro5/debug.h>
#include "objects.h"
#include "resources.h"
#include "utils.h"

void game_init();
void game_update(ALLEGRO_TIMER_EVENT event);
void key_down(ALLEGRO_KEYBOARD_EVENT event);
void key_up(ALLEGRO_KEYBOARD_EVENT event);
void game_redraw();