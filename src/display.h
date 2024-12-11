#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "emoji/angry.h"
#include "emoji/contempt.h"
#include "emoji/disgust.h"
#include "emoji/fear.h"
#include "emoji/happy.h"
#include "emoji/neutral.h"
#include "emoji/sad.h"
#include "emoji/surprise.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

extern Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void displaySetup() {
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.display();
}

void drawImageVector(const uint8_t *image, int width, int height) {
  display.clearDisplay();
  display.drawBitmap((SCREEN_WIDTH - width) / 2, (SCREEN_HEIGHT - height) / 2, image, width, height, WHITE);
  display.display();
}

#endif // DISPLAY_H
