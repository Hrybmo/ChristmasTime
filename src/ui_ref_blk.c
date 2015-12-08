/*
#include "ui_ref_blk.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_frame_tree_1_blk;
static GFont s_res_gothic_28_bold;
static GFont s_res_christmas_font_42;
static GFont s_res_gothic_18_bold;
static GFont s_res_gothic_24_bold;
static BitmapLayer *s_bitmaplayer_tree;
static TextLayer *s_textlayer_batt;
static TextLayer *s_textlayer_day;
static TextLayer *s_textlayer_hour;
static TextLayer *s_textlayer_minute;
static TextLayer *s_textlayer_temp_hi_lo;
static TextLayer *s_textlayer_temp_now;
static TextLayer *s_textlayer_date;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_frame_tree_1_blk = gbitmap_create_with_resource(RESOURCE_ID_frame_tree_1_blk);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_christmas_font_42 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_christmas_font_42));
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  // s_bitmaplayer_tree
  s_bitmaplayer_tree = bitmap_layer_create(GRect(15, 23, 111, 145));
  bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_1_blk);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_tree);
  
  // s_textlayer_batt
  s_textlayer_batt = text_layer_create(GRect(124, 151, 23, 17));
  text_layer_set_background_color(s_textlayer_batt, GColorClear);
  text_layer_set_text_color(s_textlayer_batt, GColorWhite);
  text_layer_set_text(s_textlayer_batt, "100");
  text_layer_set_text_alignment(s_textlayer_batt, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_batt);
  
  // s_textlayer_day
  s_textlayer_day = text_layer_create(GRect(0, 45, 54, 32));
  text_layer_set_background_color(s_textlayer_day, GColorClear);
  text_layer_set_text_color(s_textlayer_day, GColorWhite);
  text_layer_set_text(s_textlayer_day, "tue");
  text_layer_set_text_alignment(s_textlayer_day, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_day, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_day);
  
  // s_textlayer_hour
  s_textlayer_hour = text_layer_create(GRect(0, 0, 65, 55));
  text_layer_set_background_color(s_textlayer_hour, GColorClear);
  text_layer_set_text_color(s_textlayer_hour, GColorWhite);
  text_layer_set_text(s_textlayer_hour, "1");
  text_layer_set_text_alignment(s_textlayer_hour, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_hour, s_res_christmas_font_42);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_hour);
  
  // s_textlayer_minute
  s_textlayer_minute = text_layer_create(GRect(79, 0, 65, 55));
  text_layer_set_background_color(s_textlayer_minute, GColorClear);
  text_layer_set_text_color(s_textlayer_minute, GColorWhite);
  text_layer_set_text(s_textlayer_minute, "12");
  text_layer_set_text_alignment(s_textlayer_minute, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_minute, s_res_christmas_font_42);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_minute);
  
  // s_textlayer_temp_hi_lo
  s_textlayer_temp_hi_lo = text_layer_create(GRect(85, 70, 60, 25));
  text_layer_set_background_color(s_textlayer_temp_hi_lo, GColorClear);
  text_layer_set_text_color(s_textlayer_temp_hi_lo, GColorWhite);
  text_layer_set_text(s_textlayer_temp_hi_lo, "-20/-50");
  text_layer_set_text_alignment(s_textlayer_temp_hi_lo, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_temp_hi_lo, s_res_gothic_18_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_temp_hi_lo);
  
  // s_textlayer_temp_now
  s_textlayer_temp_now = text_layer_create(GRect(90, 50, 54, 25));
  text_layer_set_background_color(s_textlayer_temp_now, GColorClear);
  text_layer_set_text_color(s_textlayer_temp_now, GColorWhite);
  text_layer_set_text(s_textlayer_temp_now, "-23°F");
  text_layer_set_text_alignment(s_textlayer_temp_now, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_temp_now, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_temp_now);
  
  // s_textlayer_date
  s_textlayer_date = text_layer_create(GRect(0, 70, 54, 32));
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  text_layer_set_text_color(s_textlayer_date, GColorWhite);
  text_layer_set_text(s_textlayer_date, "25");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_date, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_tree);
  text_layer_destroy(s_textlayer_batt);
  text_layer_destroy(s_textlayer_day);
  text_layer_destroy(s_textlayer_hour);
  text_layer_destroy(s_textlayer_minute);
  text_layer_destroy(s_textlayer_temp_hi_lo);
  text_layer_destroy(s_textlayer_temp_now);
  text_layer_destroy(s_textlayer_date);
  gbitmap_destroy(s_res_frame_tree_1_blk);
  fonts_unload_custom_font(s_res_christmas_font_42);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_ui_ref_blk(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_ui_ref_blk(void) {
  window_stack_remove(s_window, true);
}
*/