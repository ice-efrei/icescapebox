#include <FastLED.h>

#define LED_PIN 7
#define BUTTON_PIN 2 // Changed button pin to 2
#define NUM_LEDS 36  // 3 rangées de 12 LEDs en série

CRGB leds[NUM_LEDS];  // Tableau de LEDs
bool timeToPress = false;
unsigned long pressStartTime = 0;
const unsigned long PRESS_DURATION = 5000; // 5 seconds
bool gameActive = true;

void setup() {
  randomSeed(analogRead(0));
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  gameActive = true;
}

// Blinking effect
void blinks(CRGB color, int numBlinks, int delayMs) {
  for (int j = 0; j < numBlinks; j++) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(delayMs);
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    delay(delayMs);
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

// Function to check for button press and stop
void checkButtonAndStop() {
  if (timeToPress && gameActive) {
    // Moment to press: all LEDs turn solid red
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    if (digitalRead(BUTTON_PIN) == LOW) { // Button pressed during the 5 seconds
      blinks(CRGB::Green, 5, 200); // Indicate success with green blinks
      timeToPress = false;
      gameActive = true;
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      return; // Exit the function immediately after successful press
    } else if (millis() - pressStartTime >= PRESS_DURATION) {
      blinks(CRGB::Red, 5, 400); // Indicate failure with red blinks
      gameActive = false;
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
    }
  } else if (gameActive) {
    // Check for premature button press
    if (digitalRead(BUTTON_PIN) == LOW) {
      blinks(CRGB::Red, 5, 400); // Indicate penalty with red blinks
      gameActive = false;
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      FastLED.show();
    }
  }
}

void loop() {
  if (gameActive) {
    long timer = random(60000, 300000); // Timer between 1 and 5 minutes
    unsigned long start = millis();

    while (millis() - start < timer && gameActive && !timeToPress) {
      float elapsed = millis() - start;
      float progress = elapsed / (float)timer;

      // Dégradé du vert au rouge
      for (int i = 0; i < 12; i++) {
        if (progress >= (i + 1) / 12.0) {
          uint8_t hue = map(i, 0, 11, 96, 0); // 96=Vert -> 32=Jaune -> 0=Rouge
          CRGB color = CHSV(hue, 255, 255);
          leds[i] = leds[i + 12] = leds[i + 24] = color;
        }
      }

      FastLED.show();
      delay(50); // Small delay for smoother animation

      checkButtonAndStop(); // Check for premature presses during the countdown
      if (!gameActive) break;
    }

    if (gameActive && !timeToPress) {
      fill_solid(leds, NUM_LEDS, CRGB::Red); // All LEDs turn solid red
      FastLED.show();
      timeToPress = true;
      pressStartTime = millis();
    }

    checkButtonAndStop(); // Check for button press during the 5-second window

    if (!gameActive) {
      fill_solid(leds, NUM_LEDS, CRGB::Black); // Turn off LEDs on game over
      FastLED.show();
      while (true) {
        delay(1000); // Stay in game over state
      }
    }

    delay(10); // Small delay to prevent busy-waiting
  } else {
    // Game Over state
    while (true) {
      delay(1000);
    }
  }
}
