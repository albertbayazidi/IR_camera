#include "temp_readings.h"


void test_dyn_obj(TFT_eSPI tft, int testNum){
    tft.setTextColor(TFT_WHITE,TFT_BLACK);
    tft.setCursor(CENTRE_x-130,447, 4);
    tft.print("Temp = ");

    tft.setCursor(CENTRE_x-35,440, 6);
    tft.println(testNum); 

    // tft.fillRect(1,15,478-1,304-15,TFT_BLACK);
}

