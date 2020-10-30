//file: main.c
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
#include "objects.h"
#include "game.h"
#include "utils.h"

void system_init() {
  init_or_exit(al_init(), "allegro");
  init_or_exit(al_install_keyboard(), "keyboard");
  init_or_exit(al_init_primitives_addon(), "primitives add-on");
  init_or_exit(al_init_font_addon(), "font");
  init_or_exit(al_init_ttf_addon(), "ttf-ad-on");
  init_or_exit(al_init_image_addon(), "image-ad-on");

  al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
  al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
  al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
  al_set_config_value(al_get_system_config(), "trace", "level", "debug");
  al_register_assert_handler(assert_handler);
}

void main_event_loop() {

  al_start_timer(timer);
  
  while (!done) {
    ALLEGRO_EVENT ev;
    al_wait_for_event(event_queue, &ev);
    switch (ev.type) {
    case ALLEGRO_EVENT_TIMER:
      game_update(ev.timer);
      redraw = true;
      break;
    case ALLEGRO_EVENT_DISPLAY_CLOSE:
      done = true;
      break;
    case ALLEGRO_EVENT_KEY_DOWN: key_down(ev.keyboard);
      break;
    case ALLEGRO_EVENT_KEY_UP: key_up(ev.keyboard);
      break;
    }
    if (redraw && al_is_event_queue_empty(event_queue)) {
      game_redraw();
      redraw = false;
    }
  }
}

int main(int argc, char** argv) {

  system_init();
  init_assets();
  register_events();

  game_init();

  main_event_loop();
  unregister_events();
  destroy_assets();
  return 0;
}