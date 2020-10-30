//file: resources.c
#include "resources.h"

bool done = false;
bool redraw = true;

void init_assets() {
  timer = assert_not_null(al_create_timer(REFRESH_RATE), "timer");
  event_queue = assert_not_null(al_create_event_queue(), "event queue");
  display = assert_not_null(al_create_display(WIDTH, HEIGHT), "display");
  font = assert_not_null(al_create_builtin_font(), "built-in font");
  ship_img = assert_not_null(al_load_bitmap("spaceship.png"), "Ship Image");
  al_convert_mask_to_alpha(ship_img, al_map_rgb(255, 0, 255));
  comet_img = assert_not_null(al_load_bitmap("asteroid-1-96.png"), "Astroid Image");
  exp_img = assert_not_null(al_load_bitmap("explosion_3_40_128.png"), "Explosion Image");
  title_img = assert_not_null(al_load_bitmap("SpaceShooter.png"), "Title Image");
  lost_img = assert_not_null(al_load_bitmap("GameOver.png"), "Lost Image");
  font18 = assert_not_null(al_load_font("Arcade.ttf", 30, 0), "Arcade Font");
  font = assert_not_null(al_load_ttf_font("Arcade.ttf", 64, 0), "Arcade Font");
}

void destroy_assets() {
  al_destroy_bitmap(exp_img);
  al_destroy_bitmap(comet_img);
  al_destroy_bitmap(ship_img);
  al_destroy_event_queue(event_queue);
  al_destroy_timer(timer);
  al_destroy_font(font18);
  al_destroy_display(display);
}

void register_events() {
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
}

void unregister_events() {
  al_unregister_event_source(event_queue, al_get_keyboard_event_source());
  al_unregister_event_source(event_queue, al_get_display_event_source(display));
  al_unregister_event_source(event_queue, al_get_timer_event_source(timer));
}