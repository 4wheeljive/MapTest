#include <Arduino.h>
#include <FastLED.h>
#include "fl/xymap.h"

#include "mapping.h"

#define HEIGHT 32
#define WIDTH 48
#define NUM_LEDS ( WIDTH * HEIGHT )

#define NUM_SEGMENTS 3
#define NUM_LEDS_PER_SEGMENT 512

CRGB leds[NUM_LEDS];
uint16_t ledNum;

#define DATA_PIN_1 2
#define DATA_PIN_2 3
#define DATA_PIN_3 4

using namespace fl;

//************************************************************************************************************

uint16_t myXYFunction(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    if (x >= width || y >= height) return 0;
    return loc2indProgByRow[y][x];
}

XYMap myXYmap = XYMap::constructWithUserFunction(WIDTH, HEIGHT, myXYFunction);


//************************************************************************************************************

void setup() {


   FastLED.addLeds<WS2812B, DATA_PIN_1, GRB>(leds, 0, NUM_LEDS_PER_SEGMENT)
      .setCorrection(TypicalLEDStrip);

    FastLED.addLeds<WS2812B, DATA_PIN_2, GRB>(leds, NUM_LEDS_PER_SEGMENT, NUM_LEDS_PER_SEGMENT)
      .setCorrection(TypicalLEDStrip);
   
    FastLED.addLeds<WS2812B, DATA_PIN_3, GRB>(leds, NUM_LEDS_PER_SEGMENT * 2, NUM_LEDS_PER_SEGMENT)
      .setCorrection(TypicalLEDStrip);
  
    FastLED.setBrightness(25);

    FastLED.clear();
    FastLED.show();

}

//************************************************************************************************************

void loop() {

   EVERY_N_MILLISECONDS(20) {
           
      FastLED.clear();

        for (int x = 0; x < WIDTH; x++) {
            int index = myXYmap(x, 5);
            leds[index] = CRGB::Red;
        }

        for (int x = 0; x < WIDTH; x++) {
            int index = myXYmap(x, 15);
            leds[index] = CRGB::Green;
        }

        for (int x = 0; x < WIDTH; x++) {
            int index = myXYmap(x, 25);
            leds[index] = CRGB::Blue;
        }

        FastLED.show();    

      }
}
