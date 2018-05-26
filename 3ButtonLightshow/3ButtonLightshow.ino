// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN1   2   // 1st button
#define BUTTON_PIN2   3   // 2nd button
#define BUTTON_PIN3   4   // 3rd button

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.'n\]\



#define PIXEL_COUNT 16

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState1 = HIGH;
bool oldState2 = HIGH;
bool oldState3 = HIGH;
int showType = 0;

void setup() {
  pinMode(BUTTON_PIN1, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
  startShow(showType);
  // Get current button state.
  bool newState1 = digitalRead(BUTTON_PIN1);
  bool newState2 = digitalRead(BUTTON_PIN2);
  bool newState3 = digitalRead(BUTTON_PIN3);

Serial.print("newState1:");  
Serial.println(newState1);
Serial.print("newState2:");
Serial.println(newState2);
Serial.print("newState3:");
Serial.println(newState3);

  //BUTTON 1
    newState1 = digitalRead(BUTTON_PIN1);
    if (newState1 == 1 && newState2 == 0 && newState3 == 0) {
      startShow(1);
    }
  

  // Set the last button state to the old state.
  oldState1 = newState1;
  
  //BUTTON 2
    newState2 = digitalRead(BUTTON_PIN2);
    if (newState2 == 1 && newState1 == 0 && newState3 == 0) {
      startShow(8);
    }
  
  oldState2 = newState2;
  
  //BUTTON 3
    if (newState3 == 1 && newState1 == 0 && newState2 == 0) {
      startShow(0);
    }
  
    if(newState1 == 1 && newState2 == 1 && newState3 == 0){
      startShow(3);
      }
     if(newState1 == 0 && newState2 == 1 && newState3 == 1){
      startShow(2);
     }
     if(newState1==1 && newState2==1 && newState3 == 1){
      startShow(9);
     }
     if(newState1 == 1 && newState2 == 0 && newState3 == 1){
        startShow(4);
     }
  // Set the last button state to the old state.
  oldState3 = newState3;
  Serial.print("showType = ");
  Serial.print(showType);
  Serial.println("");
  
}

void startShow(int i) {
  switch(i){
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
            break;
   case 4: colorWipe(strip.Color(150,150,150),50); // White
            break;
//    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
//            break;
//    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
//            break;
    case 7: rainbow(20);
            break;
    case 8: rainbowCycle(20);
            break;
    case 9: theaterChaseRainbow(50);
            break;
  }
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint32_t Wheel(byte WheelPos);
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel{
      if(digitalRead(BUTTON_PIN1) == 1 || digitalRead(BUTTON_PIN3) == 1){
        break;
      }
      for(i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        if(digitalRead(BUTTON_PIN1) == 1 || digitalRead(BUTTON_PIN3) == 1){
          break;
        }
      }
    strip.show();
    delay(wait);
   }
}

//Theatre-style crawling lights.
//void theaterChase(uint32_t c, uint8_t wait) {
//  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
//    for (int q=0; q < 3; q++) {
//      for (int i=0; i < strip.numPixels(); i=i+3) {
//        strip.setPixelColor(i+q, c);    //turn every third pixel on
//      }
//      strip.show();
//
//      delay(wait);
//
//      for (int i=0; i < strip.numPixels(); i=i+3) {
//        strip.setPixelColor(i+q, 0);        //turn every third pixel off
//      }
//    }
//  }
//}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  delay(1000);
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    
    if(digitalRead(BUTTON_PIN1) == 1 || digitalRead(BUTTON_PIN3) == 1 || digitalRead(BUTTON_PIN2) == 1){
        break;
    }
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
