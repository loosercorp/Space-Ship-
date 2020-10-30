#include "game.h"

static ship_t ship;
static bullet_t bullets[NUM_BULLETS];
static comet_t comets[NUM_COMETS];
static explosion_t explosions[NUM_EXPLOSIONS];

bool keys[5] = { false, false, false, false, false };
bool is_game_over = false;
enum STATE { TITLE, PLAYING, LOST };
int state = TITLE;


void game_init() {
  srand(time(NULL));
  init_ship(&ship, ship_img);
  init_bullet(&bullets, NUM_BULLETS);
  init_comet(&comets, NUM_COMETS, comet_img);
  init_explosion(explosions, NUM_EXPLOSIONS, exp_img);
}

void game_update(ALLEGRO_TIMER_EVENT event) {
 
  if (keys[UP]) {
    move_ship_up(&ship);
  } 
  else if (keys[DOWN]) {
    move_ship_down(&ship);
  } 
  else {
    reset_ship_animations(&ship, 1);
  }
  if (keys[LEFT]) {
    move_ship_left(&ship);
  } 
  else if (keys[RIGHT]) {
    move_ship_right(&ship);
  } 
  else {
    reset_ship_animations(&ship, 2);
  }
  if (state == TITLE) {
    if (keys[SPACE]) {
      state = PLAYING;
    }
  } 
  else if (state == PLAYING) {
    if (!is_game_over) {
      update_explosion(&explosions, NUM_EXPLOSIONS);
      update_bullet(&bullets, NUM_BULLETS);
      start_comet(&comets, NUM_COMETS);
      update_comet(&comets, NUM_COMETS);
      collision_bullet(&bullets, NUM_BULLETS, &comets, NUM_COMETS, &ship, &explosions, NUM_EXPLOSIONS);
      collision_comet(&comets, NUM_COMETS, &ship, &explosions, NUM_EXPLOSIONS);
      if (ship.lives <= 0) {

        is_game_over = true;
        state = LOST;
      }
    }
  } 
  else if (state == LOST) {
    if (keys[SPACE]) {
      done = true;
    }
  }
}

void key_down(ALLEGRO_KEYBOARD_EVENT event) {
  switch (event.keycode) {
  case ALLEGRO_KEY_UP: keys[UP] = true;
    break;
  case ALLEGRO_KEY_DOWN: keys[DOWN] = true;
    break;
  case ALLEGRO_KEY_LEFT: keys[LEFT] = true;
    break;
  case ALLEGRO_KEY_RIGHT: keys[RIGHT] = true;
    break;
  case ALLEGRO_KEY_SPACE: keys[SPACE] = true;
    fire_bullet(bullets, NUM_BULLETS, &ship);
    break;
  case ALLEGRO_KEY_ESCAPE: done = true;
    break;
  }
}

void key_up(ALLEGRO_KEYBOARD_EVENT event) {
  switch (event.keycode) {
  case ALLEGRO_KEY_UP: keys[UP] = false;
    break;
  case ALLEGRO_KEY_DOWN: keys[DOWN] = false;
    break;
  case ALLEGRO_KEY_RIGHT: keys[RIGHT] = false;
    break; 
  case ALLEGRO_KEY_LEFT: keys[LEFT] = false;
    break;
  case ALLEGRO_KEY_SPACE: keys[SPACE] = false;
    break;

  }
}

void game_redraw() {
  if (state == TITLE) {
    al_draw_bitmap(title_img, 0, 0, 0);
  } 
  else if (state == PLAYING) {
    if (!is_game_over) {
      draw_ship(&ship);
      draw_bullet(&bullets, NUM_BULLETS);
      draw_comet(&comets, NUM_COMETS);
      draw_explosion(&explosions, NUM_EXPLOSIONS);
      al_draw_textf(font18, al_map_rgb(255, 255, 255), 5, 5, 0, "Player has %i lives left. Player has destroyed %i objects", ship.lives, ship.score);
    }
  } 
  else if (state == LOST) {
    al_draw_bitmap(lost_img, 0, 0, 0);
    al_draw_textf(font18, al_map_rgb(255, 255, 255), 5, 5, 0, "Game Over! Score: %i", ship.score);
  }
  al_flip_display();
  al_clear_to_color(al_map_rgb(0, 0, 0));
}