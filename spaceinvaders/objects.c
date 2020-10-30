//file: objects.c
#include "objects.h"

void init_ship(ship_t* ship, ALLEGRO_BITMAP* image) {
  ship->x = 20;
  ship->y = HEIGHT / 2;
  ship->ID = PLAYER;
  ship->lives = 3;
  ship->speed = 7;
  ship->bound_x = 6;
  ship->bound_y = 7;
  ship->score = 0;
  ship->max_frame = 3;
  ship->current_frame = 0;
  ship->frame_count = 0;
  ship->frame_delay = 50;
  ship->frame_width = 46;
  ship->frame_height = 41;
  ship->animation_columns = 3;
  ship->animation_direction = 1;
  ship->animation_row = 1;
  ship->image = image;
}

void reset_ship_animations(ship_t* ship, int position) {
  if (position == 1) {
    ship->animation_row = 1;
  }
  else {
    ship->current_frame = 0;
  }
}

void draw_ship(ship_t* ship) {
  int fx = (ship->current_frame % ship->animation_columns) * ship->frame_width;
  int fy = ship->animation_row * ship->frame_height;
  al_draw_bitmap_region(ship->image, fx, fy, ship->frame_width,
    ship->frame_height, ship->x - ship->frame_width / 2, ship->y - ship->frame_height / 2, 0);
}

void move_ship_left(ship_t* ship) {
  ship->current_frame = 2;
  ship->x -= ship->speed;
  if (ship->x < 0) {
    ship->x = 0;
  }
}

void move_ship_up(ship_t* ship) {
  ship->animation_row = 0;
  ship->y -= ship->speed;
  if (ship->y < 0) {
    ship->y = 0;
  }
}

void move_ship_down(ship_t* ship) {
  ship->animation_row = 2;
  ship->y += ship->speed;
  if (ship->y > HEIGHT) {
    ship->y = HEIGHT;
  }
}

void move_ship_right(ship_t* ship) {
  ship->current_frame = 1;
  ship->x += ship->speed;
  if (ship->x > 1280) {
    ship->x = 1280;
  }
}

void init_bullet(bullet_t bullet[], int size) {
  for (int i = 0; i < size; i++) {
    bullet[i].ID = BULLET;
    bullet[i].speed = 10;
    bullet[i].live = false;
  }
}

void draw_bullet(bullet_t bullet[], int size) {
  for (int i = 0; i < size; i++) {
    if (bullet[i].live) {
      al_draw_filled_circle(bullet[i].x, bullet[i].y, 2, al_map_rgb(255, 255, 255));
    }
  }
}

void fire_bullet(bullet_t bullet[], int size, ship_t* ship) {
  for (int i = 0; i < size; i++) {
    if (!bullet[i].live) {
      bullet[i].x = ship->x + 17;
      bullet[i].y = ship->y;
      bullet[i].live = true;
      break;
    }
  }
}

void update_bullet(bullet_t bullet[], int size) {
  for (int i = 0; i < size; i++) {
    if (bullet[i].live) {
      bullet[i].x += bullet[i].speed;
      if (bullet[i].x > WIDTH) {
        bullet[i].live = false;
      }
    }
  }
}

void collision_bullet(bullet_t bullet[], int bSize, comet_t comets[], int cSize, ship_t* ship, explosion_t explosions[], int eSize) {
  for (int i = 0; i < bSize; i++) {
    if (bullet[i].live) {
      for (int j = 0; j < cSize; j++) {
        if (comets[j].live) {
          if (bullet[i].x > (comets[j].x - comets[j].bound_x) &&
            bullet[i].x < (comets[j].x + comets[j].bound_x) &&
            bullet[i].y >(comets[j].y - comets[j].bound_y) &&
            bullet[i].y < (comets[j].y + comets[j].bound_y)) {
            bullet[i].live = false;
            comets[j].live = false;
            ship->score++;
            start_explosion(explosions, eSize, bullet[i].x, bullet[i].y);
          }
        }
      }
    }
  }
}


void init_comet(comet_t comets[], int size, ALLEGRO_BITMAP* image) {
  for (int i = 0; i < size; i++) {
    comets[i].ID = ENEMY;
    comets[i].live = false;
    comets[i].speed = 2;
    comets[i].bound_x = 35;
    comets[i].bound_y = 35;
    comets[i].max_frame = 143;
    comets[i].current_frame = 0;
    comets[i].frame_count = 0;
    comets[i].frame_delay = 2;
    comets[i].frame_width = 96;
    comets[i].frame_height = 96;
    comets[i].animation_columns = 21;
    if (rand() % 2) {
      comets[i].animation_direction = 1;
    }
    else {
      comets[i].animation_direction = -1;
    }
    comets[i].image = image;
  }
}


void draw_comet(comet_t comets[], int size) {
  for (int i = 0; i < size; i++) {
    if (comets[i].live) {
      int fx = (comets[i].current_frame % comets[i].animation_columns) * comets[i].frame_width;
      int fy = (comets[i].current_frame / comets[i].animation_columns) * comets[i].frame_height;
      al_draw_bitmap_region(comets[i].image, fx, fy, comets[i].frame_width,
        comets[i].frame_height, comets[i].x - comets[i].frame_width / 2, comets[i].y - comets[i].frame_height / 2, 0);
    }
  }
}

void start_comet(comet_t comets[], int size) {
  for (int i = 0; i < size; i++) {
    if (!comets[i].live) {
      if (rand() % 500 == 0) {
        comets[i].live = true;
        comets[i].x = WIDTH;
        comets[i].y = 30 + rand() % (HEIGHT - 60);
        break;
      }
    }
  }
}

void update_comet(comet_t comets[], int size) {
  for (int i = 0; i < size; i++) {
    if (comets[i].live) {
      if (++comets[i].frame_count >= comets[i].frame_delay) {
        comets[i].current_frame += comets[i].animation_direction;
        if (comets[i].current_frame >= comets[i].max_frame) {
          comets[i].current_frame = 0;
        } 
        else if (comets[i].current_frame <= 0) {
          comets[i].current_frame = comets[i].max_frame - 1;
        }
        comets[i].frame_count = 0;
      }
      comets[i].x -= comets[i].speed;
    }
  }
}

void collision_comet(comet_t comets[], int cSize, ship_t* ship, explosion_t explosions[], int eSize) {
  for (int i = 0; i < cSize; i++) {
    if (comets[i].live) {
      if (comets[i].x - comets[i].bound_x < ship->x + ship->bound_x &&
        comets[i].x + comets[i].bound_x > ship->x - ship->bound_x &&
        comets[i].y - comets[i].bound_y < ship->y + ship->bound_y &&
        comets[i].y + comets[i].bound_y > ship->y - ship->bound_y) {
        ship->lives--;
        comets[i].live = false;
        start_explosion(explosions, eSize, ship->x, ship->y);
      } 
      else if (comets[i].x < 0) {
        comets[i].live = false;
        ship->lives--;
      }
    }
  }
}


void init_explosion(explosion_t explosions[], int size, ALLEGRO_BITMAP* image) {
  for (int i = 0; i < size; i++) {
    explosions[i].live = false;
    explosions[i].max_frame = 31;
    explosions[i].current_frame = 0;
    explosions[i].frame_count = 0;
    explosions[i].frame_delay = 1;
    explosions[i].frame_width = 128;
    explosions[i].frame_height = 128;
    explosions[i].animation_columns = 8;
    explosions[i].animation_direction = 1;
    explosions[i].image = image;
  }
}

void draw_explosion(explosion_t explosions[], int size) {
  for (int i = 0; i < size; i++) {
    if (explosions[i].live) {
      int fx = (explosions[i].current_frame % explosions[i].animation_columns) * explosions[i].frame_width;
      int fy = (explosions[i].current_frame / explosions[i].animation_columns) * explosions[i].frame_height;
      al_draw_bitmap_region(explosions[i].image, fx, fy, explosions[i].frame_width,
        explosions[i].frame_height, explosions[i].x - explosions[i].frame_width / 2, explosions[i].y - explosions[i].frame_height / 2, 0);
    }
  }
}

void start_explosion(explosion_t explosions[], int size, int x, int y) {
  for (int i = 0; i < size; i++) {
    if (!explosions[i].live) {
      explosions[i].live = true;
      explosions[i].x = x;
      explosions[i].y = y;
      break;
    }
  }
}

void update_explosion(explosion_t explosions[], int size) {
  for (int i = 0; i < size; i++) {
    if (explosions[i].live) {
      if (++explosions[i].frame_count >= explosions[i].frame_delay) {
        explosions[i].current_frame += explosions[i].animation_direction;
        if (explosions[i].current_frame >= explosions[i].max_frame) {
          explosions[i].current_frame = 0;
          explosions[i].live = false;
        }
        explosions[i].frame_count = 0;
      }
    }
  }
}