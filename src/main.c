#include <pebble.h>
#include "ui.h"
#include "callBack.h"
  
//global layers 

//module global
static int uiColor;

// Get weather update every 30 minutes
// update animation very second
// update time, date, and battery every minute
static void handle_second_tick(struct tm* tick_time, TimeUnits units_changed) {
  static uint8_t frame = 0;
  static uint8_t startDelay = 0;
  static char hour_text[] = "12";
  static char minute_text[] = "12";
  static char day_text[] = "tue";
  static char date_text[] = "29";
  static char batt_text[] = "100";
  //static char isUpdateUI = 1;
  static BatteryChargeState charge_state;
  //temperature
  static int tempUnits;
  static int temperature;
  static int temperature_hi;
  static int temperature_lo;
  static int temperatureIncoming;
  static int temperature_hiIncoming;
  static int temperature_loIncoming;
  static char temperature_hi_buffer[8];
  static char temperature_lo_buffer[8];
  static char temperature_hi_lo_buffer[16];
  static char temperature_buffer[8];
  //color
  
  
  //prevent crashing
  if(startDelay < 1)
    {
    startDelay++;
    return;
  }
  
  //change color if needed
  if(CallBack_isInvertUiColor() != uiColor)
    {
      uiColor = CallBack_isInvertUiColor();
      if(uiColor){
        ui_popStack();
        ui_blkBackgroud(); 
        ui_pushStack();
      }
      else{
        ui_popStack();
        ui_whtBackgroud();  
        ui_pushStack();
      }
    //isUpdateUI = 1;
  }
  //is weather update time 
  if((tick_time->tm_min == 0) && (tick_time->tm_sec == 0)) {
    CallBack_sendWeatherMessage();
  }
  
  //animation
  if(frame == 0)
    {
    ui_setTreeImageTo(1);
    frame++;
  }
  else
    {
    ui_setTreeImageTo(2);
    frame = 0;
  }
  
  if(clock_is_24h_style())
    {
    strftime(hour_text, sizeof(hour_text), "%H", tick_time);  
    ui_setHourTo(hour_text);
  }
  else
    {
      int hour24 = ((tick_time->tm_hour));
      strftime(hour_text, sizeof(hour_text), "%I", tick_time);
    
      if((hour24 == 10) ||
         (hour24 == 11) ||
         (hour24 == 12) ||
         (hour24 == 22) ||
         (hour24 == 23) ||
         (hour24 == 0))
      {
        ui_setHourTo(hour_text);
      }
      else
      {
        ui_setHourTo(&hour_text[1]);
      }
     }
    //minute
    strftime(minute_text, sizeof(minute_text), "%M", tick_time);
    ui_setMinuteTo(minute_text);
    
    //day
    strftime(day_text, sizeof(day_text), "%a", tick_time); //short day of week
    ui_setDayTo(day_text);

    //date
    strftime(date_text, sizeof(date_text), "%d", tick_time); //day in month
    ui_setDateTo(date_text);
    
    //battery
    charge_state = battery_state_service_peek();
    snprintf(batt_text,sizeof(batt_text), "%d", charge_state.charge_percent);
    ui_setBattTo(batt_text);
    
    tempUnits = CallBack_getTemperatureUnits();
    temperatureIncoming = CallBack_getTemperature();
    temperature_hiIncoming = CallBack_getTemperatureHigh() ;
    temperature_loIncoming = CallBack_getTemperatureLow();
    //APP_LOG(APP_LOG_LEVEL_INFO, "temperature_hiIncoming -main- %i",temperature_hiIncoming);    
    //convert temp from K
  if(tempUnits == 'F')
    {
    temperature = (((temperatureIncoming - 273.15)*1.8)+32);
    temperature_hi = (((temperature_hiIncoming - 273.15)*1.8)+32);
    temperature_lo = (((temperature_loIncoming - 273.15)*1.8)+32);
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°F", temperature);
  }
  else
    {
    temperature = (temperatureIncoming - 273.15);
    temperature_hi = (temperature_hiIncoming - 273.15);
    temperature_lo = (temperature_loIncoming - 273.15);
    snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°C", temperature);
  }
  
  //turn to text
  snprintf(temperature_hi_buffer, sizeof(temperature_hi_buffer), "%d",temperature_hi);
  snprintf(temperature_lo_buffer, sizeof(temperature_lo_buffer), "%d", temperature_lo);

	//APP_LOG(APP_LOG_LEVEL_INFO, "temperature_hi_buffer -main- %s",temperature_hi_buffer);
	//APP_LOG(APP_LOG_LEVEL_INFO, "temperature_lo_buffer %s",temperature_lo_buffer);
  //combine hi and lo temps of the day
  snprintf(temperature_hi_lo_buffer, sizeof(temperature_hi_lo_buffer), "%s/%s",temperature_hi_buffer,temperature_lo_buffer);

  if(CallBack_isWeatherDataAvailable()) {  
      ui_setTempTo(temperature_buffer);
      ui_setHiLoTempTo(temperature_hi_lo_buffer);
     }
//  }
}

void handle_init(void) {
  static struct tm *current_time;
 
  ui_init(); 
  CallBack_init();
  uiColor = CallBack_isInvertUiColor();
  //setup events
  handle_second_tick(current_time, SECOND_UNIT);
  tick_timer_service_subscribe(SECOND_UNIT, &handle_second_tick);
  
  //show the ui
  if(uiColor)
    {
      ui_blkBackgroud();
    }
    else{
      ui_whtBackgroud();  
    }
  ui_pushStack();
}

void handle_deinit(void) {
  destroy_ui();
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
