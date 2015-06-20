//    Letter:Number watchface. Shows hour as a word and the minute as a number, which I
//    I find easier to read.
//    I am a hobbyist. This code is undoubtedly embarrassing.
//    Nevertheless, it is licensed under a GNU 2.0 license. Use whatever bit of it
//    you might find helpful.
//     - David Weinberger. May 15, 2015 david@weinberger.org
//
//    version 1.1: added percentage of battery left - June 13, 2013
//    version 1.2: turned the battery info into a small graphic - June 18, 2015
// Thank you: https://ninedof.wordpress.com/2013/12/02/pebble-sdk-2-0-tutorial-1-your-first-watchapp/


#include <pebble.h>

Window *window;
TextLayer *text_layer;
InverterLayer *inv_layer;
TextLayer *text_layer_date;
TextLayer *s_battery_layer;
static BitmapLayer *s_bitmap_layer;

char buffer[] = "00:00";
char hourbuffs[] = "eight";
char hourasnumbbuff[]="99";
char fullbuff[] = "            ";
char hourstring[] = "      ";
char datebuff[] ="ee00/00/2015";
static GBitmap *s_batteryimg_bitmap;
char percentofbattery[] = "charging";
int batterypercent;
int gbatterypercent = 0;


// Battery stuff
static void battery_handler(BatteryChargeState charge_state) {
   static char battery_text[] = "Charging";
//APP_LOG(APP_LOG_LEVEL_DEBUG, "13");
  // ---- text display
  if (charge_state.is_charging) {
    snprintf(battery_text, sizeof(battery_text), "charging");
 } else {
   snprintf(battery_text, sizeof(battery_text), "%d%%", charge_state.charge_percent);
  }
 text_layer_set_text(s_battery_layer, battery_text);
  
  batterypercent = charge_state.charge_percent; 
  
 if (batterypercent == 00){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery00);
  }
  if (batterypercent == 10){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery10);
  }
 if (batterypercent == 20){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery20);
  }
  if (batterypercent == 30){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery30);
  } 
  if (batterypercent == 40){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery40);
  }
  if (batterypercent == 50){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery50);
  }
   if (batterypercent == 60){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery60);
  }
  if (batterypercent == 70){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery70);
  } 
  if (batterypercent == 80){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery80);
  }
  if (batterypercent == 90){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery90);
  }
  if (batterypercent == 100){
     s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_battery00);
  }
  if (charge_state.is_charging){
      s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_batterych);
  }
  
  
  //s_bitmap_layer = bitmap_layer_create(GRect(00, 00, 23, 23));
 //  s_bitmap_layer = bitmap_layer_create(GRect(70, 00, 89, 07));
  // set bitmap to the new one
  bitmap_layer_set_bitmap(s_bitmap_layer, s_batteryimg_bitmap );
  
}


// tick handler
void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{
    
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
   //strftime(fullbuff, sizeof("           "), strcat(hourstring,"\n%M"), tick_time);
   strftime(fullbuff, strlen(hourstring) + 4, strcat(hourstring,"\n%M"), tick_time);
  
 
    //Change the TextLayer text to show the new time!
    text_layer_set_text(text_layer, fullbuff);
  
   // change date layer
    static char s_date_text[] = "Xxxxxxxxx 00";
    strftime(s_date_text, sizeof(s_date_text), "%B %e", tick_time);
    text_layer_set_text(text_layer_date, s_date_text);
  
  // check battery
  //handle_battery(battery_state_service_peek());
  
}
 
void window_load(Window *window)
{
 
  
  // create date layer
  text_layer_date = text_layer_create(GRect(0, 118,132,168));
  text_layer_set_background_color(text_layer_date, GColorClear);
  text_layer_set_text_color(text_layer_date, GColorBlack);
   text_layer_set_text_alignment(text_layer_date, GTextAlignmentCenter);
  text_layer_set_font(text_layer_date, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  
  
  // Create Time layer
  text_layer = text_layer_create(GRect(0, 0, 132, 168));
  text_layer_set_background_color(text_layer, GColorClear);
  text_layer_set_text_color(text_layer, GColorBlack);
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  
  // Create text battery layer
  s_battery_layer = text_layer_create(GRect(0, 140,132, 168));
 text_layer_set_text_color(s_battery_layer, GColorBlack);
 text_layer_set_background_color(s_battery_layer, GColorClear);
 text_layer_set_font(s_battery_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18));
 text_layer_set_text_alignment(s_battery_layer, GTextAlignmentCenter);
  text_layer_set_text(s_battery_layer, "-");
  
  // create battery image layer
  // temp battery image to load
  //s_batteryimg_bitmap = gbitmap_create_with_resource(RESOURCE_ID_batterych);
  s_bitmap_layer = bitmap_layer_create(GRect(70, 00, 89, 07));
  //bitmap_layer_set_bitmap(s_bitmap_layer, s_batteryimg_bitmap );
   // check battery
  battery_handler(battery_state_service_peek());
  
  
  // load external (non-system) font
  ResHandle font_handle = resource_get_handle(RESOURCE_ID_VERDANA_38);
  text_layer_set_font(text_layer, fonts_load_custom_font(font_handle));
   
  //add  hour/min layer
  layer_add_child(window_get_root_layer(window), (Layer*) text_layer);
  // add date layer
  layer_add_child(window_get_root_layer(window), (Layer*) text_layer_date);
  // add battery text layer
  layer_add_child(window_get_root_layer(window), (Layer*) s_battery_layer);
  // layer_add_child(window_get_root_layer(window), (Layer*) s_bitmap_layer);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bitmap_layer));

  
  //Inverter layer so the background is black
  inv_layer = inverter_layer_create(GRect(0, 0, 200,200));
  //inv_layer = inverter_layer_create(GRect(0, 50, 144, 62));
  layer_add_child(window_get_root_layer(window), (Layer*) inv_layer);
  


}
 
void window_unload(Window *window)
{
   text_layer_destroy(text_layer);
   text_layer_destroy(text_layer_date);
   inverter_layer_destroy(inv_layer);
   // gbitmap_destroy(s_batteryimg_bitmap);
   bitmap_layer_destroy(s_bitmap_layer);
}
 
void init()
{
  //Initialize the app elements
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  window_stack_push(window, true);
  tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);
  
  // check battery
  battery_state_service_subscribe(battery_handler);
}
 
void deinit()
{
   window_destroy(window);
  tick_timer_service_unsubscribe();
  
}
 
int main(void)
{
  init();
  app_event_loop();
  deinit();
}
