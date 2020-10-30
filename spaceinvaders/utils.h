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
#include "game.h"

void init_or_exit(bool is_initialized, const char* name);
void* assert_not_null(void* ptr, const char* name);
void assert_handler(const char* expr, const char* file, int line, const char* func);