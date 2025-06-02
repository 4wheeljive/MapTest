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

#define BLUR_AMOUNT 172

//************************************************************************************************************

uint16_t myXYFunction(uint16_t x, uint16_t y, uint16_t width, uint16_t height) {
    width = WIDTH;
    height = HEIGHT;
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

void threeLines(){ 
    EVERY_N_MILLISECONDS(50){
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

void colorChase() {
  for ( uint8_t y = 0 ; y < HEIGHT ; y++ ) {
    for ( uint8_t x = 0 ; x < WIDTH ; x++ ) {
      leds[myXYmap(x, y)] = CRGB::Green;
      FastLED.delay(5);
      FastLED.show();
    }
  }
}

void randomBlur() {
    static int x = random(WIDTH);
    static int y = random(HEIGHT);
    static CRGB c = CRGB(0, 0, 0);
    blur2d(leds, WIDTH, HEIGHT, BLUR_AMOUNT, myXYmap);
    EVERY_N_MILLISECONDS(1000) {
        x = random(WIDTH);
        y = random(HEIGHT);
        uint8_t r = random(255);
        uint8_t g = random(255);
        uint8_t b = random(255);
        c = CRGB(r, g, b);
    }
    leds[myXYmap(x,y)] = c;
    FastLED.show();
}

//************************************************************************************************************

void loop() {

    //colorChase();
    threeLines();
    //randomBlur();

 }
