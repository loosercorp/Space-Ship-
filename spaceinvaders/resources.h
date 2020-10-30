//file: resources.h

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
#include "game.h"
#include "utils.h"
#include "objects.h"

#define WIDTH 1280
#define HEIGHT 720 
#define FPS 60
#define NUM_BULLETS 5
#define NUM_COMETS 5
#define NUM_EXPLOSIONS 5
#define REFRESH_RATE (1.0 / FPS)

extern bool redraw;
extern bool done;
extern int state;
enum KEYS { UP, DOWN, LEFT, RIGHT, SPACE };

ALLEGRO_DISPLAY* display;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_FONT* font18;
ALLEGRO_FONT* font;
ALLEGRO_BITMAP* ship_img;
ALLEGRO_BITMAP* comet_img;
ALLEGRO_BITMAP* exp_img;
ALLEGRO_BITMAP* title_img;
ALLEGRO_BITMAP* lost_img;

void init_assets();
void destroy_assets();

void register_events();
void unregister_events();