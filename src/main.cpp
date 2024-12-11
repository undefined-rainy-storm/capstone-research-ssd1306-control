#include <Arduino.h>
#include "display.h"

extern Adafruit_SSD1306 display;

const uint8_t* emojis[] = {happy, sad, neutral, surprise, fear, disgust, contempt, angry};
const int emojiCount = sizeof(emojis) / sizeof(emojis[0]);

void setup() {
  // put your setup code here, to run once:
  displaySetup();
  drawImageVector(happy, 64, 64);
}

void loop() {
  // Generate a random index for the emoji array
  int randomIndex = random(0, emojiCount);

  // Generate a random delay time based on a standard distribution
  // For simplicity, we use a uniform distribution here
  int randomDelay = random(1000, 5000); // Random delay between 1 and 5 seconds

  // Display the random emoji
  drawImageVector(emojis[randomIndex], 64, 64);

  // Wait for the random delay time
  delay(randomDelay);
}
