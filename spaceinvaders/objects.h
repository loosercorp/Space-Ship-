//file: objects.h
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
#include "resources.h"
#include "game.h"
#include "utils.h"

enum IDS { PLAYER, BULLET, ENEMY };

typedef struct {
  int ID;
  int x;
  int y;
  int lives;
  int speed;
  int bound_x;
  int bound_y;
  int score;
  int max_frame;
  int current_frame;
  int frame_count;
  int frame_delay;
  int frame_width;
  int frame_height;
  int animation_columns;
  int animation_direction;
  int animation_row;
  ALLEGRO_BITMAP* image;
}ship_t;

typedef struct {
  int ID;
  int x;
  int y;
  bool live;
  int speed;
}bullet_t;

typedef struct {
  int ID;
  int x;
  int y;
  bool live;
  int speed;
  int bound_x;
  int bound_y;
  int max_frame;
  int current_frame;
  int frame_count;
  int frame_delay;
  int frame_width;
  int frame_height;
  int animation_columns;
  int animation_direction;
  ALLEGRO_BITMAP* image;
}comet_t;

typedef struct {
  int x;
  int y;
  bool live;
  int max_frame;
  int current_frame;
  int frame_count;
  int frame_delay;
  int frame_width;
  int frame_height;
  int animation_columns;
  int animation_direction;
  ALLEGRO_BITMAP* image;
}explosion_t;

void init_ship(ship_t* ship, ALLEGRO_BITMAP* image);
void reset_ship_animations(ship_t* ship, int position);
void draw_ship(ship_t* ship);
void move_ship_left(ship_t* ship);
void move_ship_up(ship_t* ship);
void move_ship_down(ship_t* ship);
void move_ship_right(ship_t* ship);

void init_bullet(bullet_t bullet[], int size);
void draw_bullet(bullet_t bullet[], int size);
void fire_bullet(bullet_t bullet[], int size, ship_t* ship);
void update_bullet(bullet_t bullet[], int size);
void collision_bullet(bullet_t bullet[], int bullet_size, comet_t comets[], int comet_size, ship_t* ship, explosion_t explosions[], int explosion_size);


void init_comet(comet_t comets[], int size, ALLEGRO_BITMAP* image);
void draw_comet(comet_t comets[], int size);
void start_comet(comet_t comets[], int size);
void update_comet(comet_t comets[], int size);
void collision_comet(comet_t comets[], int comet_size, ship_t* ship, explosion_t explosions[], int explosion_size);


void init_explosion(explosion_t explosions[], int size, ALLEGRO_BITMAP* image);
void draw_explosion(explosion_t explosions[], int size);
void start_explosion(explosion_t explosions[], int size, int x, int y);
void update_explosion(explosion_t explosions[], int size);

//void ChangeState(int state, int newState);
