#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

uint8_t dessin[8][12] = {
  {0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0}
};

void setup() {
  matrix.begin();
  matrix.renderBitmap(dessin, 8, 12);
}

void loop() {
}