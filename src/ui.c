#include <pebble.h>
#include "ui.h"

//prototypes
static void canvas_update_proc(Layer *this_layer, GContext *ctx);  
  
// globals 
Window *s_window;
GBitmap *s_res_frame1_color;
#if defined(PBL_COLOR)
GBitmap *s_res_frame_tree_1_color;
GBitmap *s_res_frame_tree_2_color;
#else
GBitmap *s_res_frame_tree_1;
GBitmap *s_res_frame_tree_2;
GBitmap *s_res_frame_tree_1_blk;
GBitmap *s_res_frame_tree_2_blk;
#endif
GFont s_res_christmas_font_42;
GFont s_res_gothic_24_bold;
GFont s_res_gothic_18_bold;
GFont s_res_gothic_28_bold;
BitmapLayer *s_bitmaplayer_tree;
TextLayer *s_textlayer_hour;
TextLayer *s_textlayer_minute;
TextLayer *s_textlayer_day;
TextLayer *s_textlayer_date;
TextLayer *s_textlayer_temp_now;
TextLayer *s_textlayer_temp_hi_lo;  
Layer *s_canvas_layer;
TextLayer *s_textlayer_batt;

int isInvert = 0;

//------------------------------------------------------------------
void ui_init(void)
  {
	#ifdef PBL_ROUND
	#define ROUND_OFFSET 15
	#define BATT_OFFSET 7
	#else
	#define ROUND_OFFSET 0
	#define BATT_OFFSET 0
	#endif
	s_window = window_create();
	
	#ifdef PBL_SDK_2
  window_set_fullscreen(s_window, true); 
  #endif
	
	window_set_background_color(s_window, GColorClear);
	#if defined(PBL_COLOR)
	s_res_frame_tree_1_color = gbitmap_create_with_resource(RESOURCE_ID_frame1_color);
	s_res_frame_tree_2_color = gbitmap_create_with_resource(RESOURCE_ID_frame2_color);
	#else
	s_res_frame_tree_1 = gbitmap_create_with_resource(RESOURCE_ID_frame_tree_1);
  s_res_frame_tree_2 = gbitmap_create_with_resource(RESOURCE_ID_frame_tree_2);
  s_res_frame_tree_1_blk = gbitmap_create_with_resource(RESOURCE_ID_frame_tree_1_blk);
  s_res_frame_tree_2_blk = gbitmap_create_with_resource(RESOURCE_ID_frame_tree_2_blk);
	#endif
  
  s_res_christmas_font_42 = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_christmas_font_42));
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_18_bold = fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD); 
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
	
  s_textlayer_day = text_layer_create(GRect(0+ROUND_OFFSET, 45+ROUND_OFFSET, 54, 32));
  s_textlayer_date = text_layer_create(GRect(0+ROUND_OFFSET, 70+ROUND_OFFSET, 54, 32));
  s_textlayer_temp_now = text_layer_create(GRect(90+ROUND_OFFSET, 50+ROUND_OFFSET, 54, 25));
  s_textlayer_temp_hi_lo = text_layer_create(GRect(85+ROUND_OFFSET, 70+ROUND_OFFSET, 60, 25));
  s_textlayer_hour = text_layer_create(GRect(0+ROUND_OFFSET, 0+ROUND_OFFSET, 65, 55));
  s_textlayer_minute = text_layer_create(GRect(79+ROUND_OFFSET, 0+ROUND_OFFSET, 65, 55));
  s_textlayer_batt = text_layer_create(GRect(124+BATT_OFFSET, 151-ROUND_OFFSET, 23, 17));
  s_canvas_layer = layer_create(GRect(0+ROUND_OFFSET,0+ROUND_OFFSET,144,158));
  s_bitmaplayer_tree = bitmap_layer_create(GRect(15+ROUND_OFFSET, 23+ROUND_OFFSET, 111, 145));
	#if defined(PBL_COLOR)
	bitmap_layer_set_compositing_mode(s_bitmaplayer_tree, GCompOpSet);
	#endif
	layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_tree);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_day);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_date);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_temp_now);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_temp_hi_lo);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_hour);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_minute);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_batt);
  layer_add_child(window_get_root_layer(s_window), s_canvas_layer);
  layer_set_update_proc(s_canvas_layer, canvas_update_proc);
	
  setlocale(LC_ALL, ""); //support all languages
}


//------------------------------------------------------------------
static void canvas_update_proc(Layer *this_layer, GContext *ctx) {  
  static GPoint p0;
  static GPoint p1;
	
  if(isInvert){
    graphics_context_set_stroke_color(ctx, GColorWhite);
  }
  else{
    graphics_context_set_stroke_color(ctx, GColorBlack);
  }
  
  // Draw the line under hour
  p0.x = 0;
  p0.y = 50;
  p1.x = 60;
  p1.y = 50;
  graphics_draw_line(ctx,p0, p1);
  

  // Draw the line under minute
  p0.x = 85;
  p0.y = 50;
  p1.x = 158;
  p1.y = 50;
  graphics_draw_line(ctx,p0, p1);
	
	
}
//-------------------------------------------------------------------
void ui_whtBackgroud(void) {

  window_set_background_color(s_window, GColorWhite);
  
  isInvert = 0;
	#if defined(PBL_COLOR)
	bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_1_color);
	#else
  bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_1);
  #endif 
  text_layer_set_background_color(s_textlayer_day, GColorClear);
  text_layer_set_text_color(s_textlayer_day, GColorBlack);
  text_layer_set_text(s_textlayer_day, "");
  text_layer_set_text_alignment(s_textlayer_day, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_day, s_res_gothic_28_bold);
   
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  text_layer_set_text_color(s_textlayer_date, GColorBlack);
  text_layer_set_text(s_textlayer_date, "");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_date, s_res_gothic_28_bold);
    
  text_layer_set_background_color(s_textlayer_temp_now, GColorClear);
  text_layer_set_text_color(s_textlayer_temp_now, GColorBlack);
  text_layer_set_text(s_textlayer_temp_now, "");
  text_layer_set_text_alignment(s_textlayer_temp_now, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_temp_now, s_res_gothic_24_bold);
    
  text_layer_set_background_color(s_textlayer_temp_hi_lo, GColorClear);
  text_layer_set_text_color(s_textlayer_temp_hi_lo, GColorBlack);
  text_layer_set_text(s_textlayer_temp_hi_lo, "");
  text_layer_set_text_alignment(s_textlayer_temp_hi_lo, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_temp_hi_lo, s_res_gothic_18_bold);
   
  text_layer_set_background_color(s_textlayer_hour, GColorClear);
  text_layer_set_text_color(s_textlayer_hour, GColorBlack);
  text_layer_set_text(s_textlayer_hour, "");
  text_layer_set_text_alignment(s_textlayer_hour, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_hour, s_res_christmas_font_42);
 
  text_layer_set_background_color(s_textlayer_minute, GColorClear);
  text_layer_set_text_color(s_textlayer_minute, GColorBlack);
  text_layer_set_text(s_textlayer_minute, "");
  text_layer_set_text_alignment(s_textlayer_minute, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_minute, s_res_christmas_font_42);
    
  text_layer_set_background_color(s_textlayer_batt, GColorClear);
  text_layer_set_text_color(s_textlayer_batt, GColorBlack);
  text_layer_set_text(s_textlayer_batt, "");
  text_layer_set_text_alignment(s_textlayer_batt, GTextAlignmentCenter);
}
//------------------------------------------------------------------------
void ui_pushStack(void)
{
  window_stack_push(s_window, true);
}
//------------------------------------------------------------------------
void ui_popStack(void)
{
  window_stack_push(s_window, true);
}
//-----------------------------------------------------------------------------
void ui_setTreeImageTo(int num)
  {
  if(num == 1)
  {
		#if defined(PBL_COLOR)
		bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_1_color);
		#else
		if(isInvert){
      bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_1_blk);
    }
    else{
      bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_1);
    }
		#endif  
  }
  else
  {
		#if defined(PBL_COLOR)
		bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_2_color);
		#else
    if(isInvert){
      bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_2_blk);
    }
    else{
      bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_2);
    }
		#endif
  }
}
//------------------------------------------------------------------------
void ui_setTempTo(char *buff)
  {
  text_layer_set_text(s_textlayer_temp_now, buff);
}
//-----------------------------------------------------------------------
void ui_setHiLoTempTo(char *buff)
  {
  text_layer_set_text(s_textlayer_temp_hi_lo, buff);
}
//---------------------------------------------------------------------
void ui_setDayTo(char *buff)
  {
  text_layer_set_text(s_textlayer_day, buff);
}
//--------------------------------------------------------------------
void ui_setDateTo(char *buff)
  {
  text_layer_set_text(s_textlayer_date, buff);
}
//---------------------------------------------------------------------
void ui_setHourTo(char *buff)
  {
  text_layer_set_text(s_textlayer_hour, buff);
}
//---------------------------------------------------------------------
void ui_setMinuteTo(char *buff)
  {
  text_layer_set_text(s_textlayer_minute, buff);
}
//------------------------------------------------------------------------
void ui_setBattTo(char *buff)
  {
  text_layer_set_text(s_textlayer_batt, buff);
}
//-------------------------------------------------------------------------------
void ui_blkBackgroud(void)
  {
  window_set_background_color(s_window, GColorBlack);
  
  isInvert = 1;
  
	#if defined(PBL_COLOR)
	bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_1_color);
	#else
  bitmap_layer_set_bitmap(s_bitmaplayer_tree, s_res_frame_tree_1_blk);
  #endif 
  
  text_layer_set_background_color(s_textlayer_batt, GColorClear);
  text_layer_set_text_color(s_textlayer_batt, GColorWhite);
  text_layer_set_text(s_textlayer_batt, "");
  text_layer_set_text_alignment(s_textlayer_batt, GTextAlignmentCenter);
  
  text_layer_set_background_color(s_textlayer_day, GColorClear);
  text_layer_set_text_color(s_textlayer_day, GColorWhite);
  text_layer_set_text(s_textlayer_day, "");
  text_layer_set_text_alignment(s_textlayer_day, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_day, s_res_gothic_28_bold);
  
  text_layer_set_background_color(s_textlayer_hour, GColorClear);
  text_layer_set_text_color(s_textlayer_hour, GColorWhite);
  text_layer_set_text(s_textlayer_hour, "");
  text_layer_set_text_alignment(s_textlayer_hour, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_hour, s_res_christmas_font_42);
  
  text_layer_set_background_color(s_textlayer_minute, GColorClear);
  text_layer_set_text_color(s_textlayer_minute, GColorWhite);
  text_layer_set_text(s_textlayer_minute, "");
  text_layer_set_text_alignment(s_textlayer_minute, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_minute, s_res_christmas_font_42);
  
  text_layer_set_background_color(s_textlayer_temp_hi_lo, GColorClear);
  text_layer_set_text_color(s_textlayer_temp_hi_lo, GColorWhite);
  text_layer_set_text(s_textlayer_temp_hi_lo, "");
  text_layer_set_text_alignment(s_textlayer_temp_hi_lo, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_temp_hi_lo, s_res_gothic_18_bold);
  
  text_layer_set_background_color(s_textlayer_temp_now, GColorClear);
  text_layer_set_text_color(s_textlayer_temp_now, GColorWhite);
  text_layer_set_text(s_textlayer_temp_now, "");
  text_layer_set_text_alignment(s_textlayer_temp_now, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_temp_now, s_res_gothic_24_bold);
  
  text_layer_set_background_color(s_textlayer_date, GColorClear);
  text_layer_set_text_color(s_textlayer_date, GColorWhite);
  text_layer_set_text(s_textlayer_date, "");
  text_layer_set_text_alignment(s_textlayer_date, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_date, s_res_gothic_28_bold);
  
}

void destroy_ui(void) {
  bitmap_layer_destroy(s_bitmaplayer_tree);
  text_layer_destroy(s_textlayer_day);
  text_layer_destroy(s_textlayer_date);
  text_layer_destroy(s_textlayer_temp_now);
  text_layer_destroy(s_textlayer_temp_hi_lo);
  text_layer_destroy(s_textlayer_hour);
  text_layer_destroy(s_textlayer_minute);
	#ifdef PBL_COLOR
	gbitmap_destroy(s_res_frame_tree_1_color);
  gbitmap_destroy(s_res_frame_tree_2_color);
	#else
  gbitmap_destroy(s_res_frame_tree_1);
  gbitmap_destroy(s_res_frame_tree_2);
  gbitmap_destroy(s_res_frame_tree_1_blk);
  gbitmap_destroy(s_res_frame_tree_2_blk);
	#endif
  text_layer_destroy(s_textlayer_batt);
  layer_destroy(s_canvas_layer);
  fonts_unload_custom_font(s_res_christmas_font_42);
  window_destroy(s_window);
}
