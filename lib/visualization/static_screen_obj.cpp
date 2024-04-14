#include "temp_readings.h"

void screen_setup(TFT_eSPI tft){
    
    tft.init();
    tft.setRotation(2);

    tft.fillScreen(TFT_BLACK);

    // Header 
    tft.setTextColor(TFT_BLACK, TFT_RED);
    tft.fillRect(0, 0, 320, 30, TFT_RED);
    tft.drawCentreString("Temp readings", CENTRE_x, 3, 4);

    // Border
    tft.drawRect(0, 30, 320, 400, TFT_RED);

    // Footer
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setCursor(CENTRE_x + 70, 447, 4);
    tft.println("Wifi on"); 
}

