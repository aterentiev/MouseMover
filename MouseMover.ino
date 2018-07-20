//
// Automatic mouse movement preventing PC sleep mode or screensaver
// Alexandre Terentiev, V1.0, 2018-29
// Based on DigiSpark hardware (http://digistump.com/products/1)
// Uses DigiMouse library from DigiStump Arduino repository (Board manager URL: http://digistump.com/package_digistump_index.json)
// Licensed under CC-BY-SA 3.0 terms (https://creativecommons.org/licenses/by-sa/3.0/)
//

#include <DigiMouse.h>

const int LED_PIN = 1;
const unsigned long MOVE_TIMEOUT = 50000; // 50s between movements
const unsigned long UPDATE_TIMEOUT = 25; // 25ms between mouse updates
const unsigned long LED_TIMEOUT = 300; // 300ms LED blinks
const char MOVE_X = 1;
const char MOVE_Y = 1; 

// The mouse will move every MOVE_TIMEOUT milliseconds to (MOVE_X, MOVE_Y) points and back
// To indicate that the mouse movement is running, the LED on LED_PIN will flash every LED_TIMEOUT ms
// Mouse updates are done every UPDATE_TIMEOUT ms (it shoud be at least every 50ms)

bool toggle, led;
unsigned long ms, move_timeout, update_timeout, led_timeout;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  DigiMouse.begin(); //start or reenumerate USB
}

void loop() {
  ms = millis();
  if ((ms - move_timeout) > MOVE_TIMEOUT) {
    toggle = !toggle;
    if (toggle) {
      DigiMouse.move(MOVE_X, MOVE_Y, 0);
    } else {
      DigiMouse.move(-1 * MOVE_X, -1 * MOVE_Y, 0);
    }
    move_timeout = ms;
  }
  if ((ms - update_timeout) > UPDATE_TIMEOUT) {
    DigiMouse.update();
    update_timeout = ms;
  }
  if ((ms - led_timeout) > LED_TIMEOUT) {
    led = !led;
    digitalWrite(LED_PIN, led);
    led_timeout = ms;
  }
}

