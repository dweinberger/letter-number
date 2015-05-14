#include <pebble.h>
 // Thank you: https://ninedof.wordpress.com/2013/12/02/pebble-sdk-2-0-tutorial-1-your-first-watchapp/


  
Window *window;
TextLayer *text_layer;
InverterLayer *inv_layer;
TextLayer *text_layer_date;
char buffer[] = "00:00";
char hourbuffs[] = "eight";
char hourasnumbbuff[]="99";
char fullbuff[] = "00++EIGHTEEN";
char hourstring[] = "EIGHT";
char datebuff[] ="ee00/00/2015";

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
    //Format the buffer string using tick_time as the time source
    //strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
    // get the hour as a string
    strftime(hourasnumbbuff, sizeof("00"), "%H", tick_time);
  if ( (!strcmp(hourasnumbbuff, "01")) || (!strcmp(hourasnumbbuff, "13")) ){
      strcpy(hourstring, "one") ;
    }
  if ( (!strcmp(hourasnumbbuff, "02")) || (!strcmp(hourasnumbbuff, "14")) ){
      strcpy(hourstring, "two") ;
    }
  if ( (!strcmp(hourasnumbbuff, "03")) || (!strcmp(hourasnumbbuff, "15")) ){
      strcpy(hourstring, "three") ;
    }
   if ( (!strcmp(hourasnumbbuff, "04")) || (!strcmp(hourasnumbbuff, "16")) ){
      strcpy(hourstring, "four") ;
    }
   if ( (!strcmp(hourasnumbbuff, "05")) || (!strcmp(hourasnumbbuff, "17")) ){
      strcpy(hourstring, "five") ;
    }
   if ( (!strcmp(hourasnumbbuff, "06")) || (!strcmp(hourasnumbbuff, "18")) ){
      strcpy(hourstring, "six") ;
    }
   if ( (!strcmp(hourasnumbbuff, "07")) || (!strcmp(hourasnumbbuff, "19")) ){
      strcpy(hourstring, "seven") ;
    }
   if ( (!strcmp(hourasnumbbuff, "08")) || (!strcmp(hourasnumbbuff, "20")) ){
      strcpy(hourstring, "eight") ;
    }
   if ( (!strcmp(hourasnumbbuff, "09")) || (!strcmp(hourasnumbbuff, "21")) ){
      strcpy(hourstring, "nine") ;
    }
   if ( (!strcmp(hourasnumbbuff, "10")) || (!strcmp(hourasnumbbuff, "22")) ){
      strcpy(hourstring, "ten") ;
    }
   if ( (!strcmp(hourasnumbbuff, "11")) || (!strcmp(hourasnumbbuff, "23")) ){
      strcpy(hourstring, "eleven") ;
    }
   if ( (!strcmp(hourasnumbbuff, "12")) || (!strcmp(hourasnumbbuff, "00")) || (!strcmp(hourasnumbbuff, "24")) ){
      strcpy(hourstring, "twelve") ;
    }
    strftime(fullbuff, sizeof("0            "), strcat(hourstring,"\n%M"), tick_time);
  
 
    //Change the TextLayer text to show the new time!
    text_layer_set_text(text_layer, fullbuff);
  
   // change date layer
  //strftime(s_date_text, sizeof(s_date_text), "%B %e", tick_time);
  //text_layer_set_text(s_date_layer, s_date_text);
  static char s_date_text[] = "Xxxxxxxxx 00";
    strftime(s_date_text, sizeof(s_date_text), "%B %e", tick_time);
    text_layer_set_text(text_layer_date, s_date_text);
  
}


 
void window_load(Window *window)
{
 
  
  // create date layer
  text_layer_date = text_layer_create(GRect(0, 118,132,168));
  text_layer_set_background_color(text_layer_date, GColorClear);
  text_layer_set_text_color(text_layer_date, GColorBlack);
   text_layer_set_text_alignment(text_layer_date, GTextAlignmentCenter);
  text_layer_set_font(text_layer_date, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  
  
 
  // strftime(datebuff, sizeof("ee00/00/2015"), strcat(hourstring,"\n%M"), tick_time);
  // strcat(datebuff,"11/22/1234");
  //text_layer_set_text(text_layer_date, datebuff);
  
  //Get a time structure so that the face doesn't start blank
  //struct tm *t;
  //time_t temp;
  //temp = time(NULL);
  //t = localtime(&temp);
 
  //Manually call the tick handler when the window is loading
  //tick_handler(t, MINUTE_UNIT);
  // format it
  //text_layer = text_layer_create(GRect(0, 53, 132, 168));
  
  // Create Time layer
  text_layer = text_layer_create(GRect(0, 0, 132, 168));
  text_layer_set_background_color(text_layer, GColorClear);
  text_layer_set_text_color(text_layer, GColorBlack);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  //FONT_KEY_BITHAM_30_BLACK
    // load font
  ResHandle font_handle = resource_get_handle(RESOURCE_ID_VERDANA_38);
  text_layer_set_font(text_layer, fonts_load_custom_font(font_handle));
  //text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK));
   
  //add  hour/min layer
  layer_add_child(window_get_root_layer(window), (Layer*) text_layer);
  // add date layer
  layer_add_child(window_get_root_layer(window), (Layer*) text_layer_date);
  
  //Inverter layer
  inv_layer = inverter_layer_create(GRect(0, 0, 200,200));
  //inv_layer = inverter_layer_create(GRect(0, 50, 144, 62));
  layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
  //layer_add_child(window_get_root_layer(window), (Layer*) text_layer_date);
}
 
void window_unload(Window *window)
{
   text_layer_destroy(text_layer);
   inverter_layer_destroy(inv_layer);
}
 
void init()
{
  //Initialize the app elements here!
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
  tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);
}
 
void deinit()
{
  //text_layer_destroy(text_layer);
 window_destroy(window);
  tick_timer_service_unsubscribe();
  
}
 
int main(void)
{
  init();
  app_event_loop();
  deinit();
}