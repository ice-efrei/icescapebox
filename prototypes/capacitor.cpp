#include <FastLED.h>

#define LED_PIN 7
#define BUTTON_PIN 2 // Changed button pin to 2
#define NUM_LEDS 36  // 3 rangées de 12 LEDs en série

CRGB leds[NUM_LEDS];  // Tableau de LEDs
int lives = 5;        // Initial number of lives
bool timeToPress = false;
unsigned long pressStartTime = 0;
const unsigned long PRESS_DURATION = 5000; // 5 seconds

void setup() {
  Serial.begin(9600); // Initialize serial communication
  randomSeed(analogRead(0));
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up resistor
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  Serial.print("Starting with ");
  Serial.print(lives);
  Serial.println(" lives.");
}

// Blinking effect
void blinks(CRGB color) {
  CRGB temp[NUM_LEDS];
  for (int i = 0; i < NUM_LEDS; i++) {
    temp[i] = leds[i];
  }
  for (int j = 0; j < 5; j++) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(200);
    fill_solid(leds, NUM_LEDS, color);
    FastLED.show();
    delay(200);
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

// Function to check for button press and reset
void checkButtonAndReset() {
  if (timeToPress) {
    if (digitalRead(BUTTON_PIN) == LOW) { // Button press detected (LOW because of pull-up)
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      timeToPress = false;
      Serial.println("Button pressed in time! LEDs reset.");
    } else if (millis() - pressStartTime >= PRESS_DURATION) {
      lives--;
      Serial.print("Time's up! Lives remaining: ");
      Serial.println(lives);
      blinks(CRGB::Red); // Indicate failure with red blinks
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      timeToPress = false;
    }
  } else {
    // Check for premature button press
    if (digitalRead(BUTTON_PIN) == LOW) {
      lives--;
      Serial.print("Premature button press! Lives remaining: ");
      Serial.println(lives);
      blinks(CRGB::Red); // Indicate penalty with red blinks
      delay(1000); // Small delay to show the penalty blink
    }
  }
}

void loop() {
  if (lives <= 0) {
    Serial.println("Game Over!");
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    FastLED.show();
    while (true) {
      delay(1000); // Stay in game over state
    }
  }

  long timer = random(60000, 300000); // Timer between 1 minute (60000 ms) and 5 minutes (300000 ms)
  unsigned long start = millis();

  while (millis() - start < timer && !timeToPress) {
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

    checkButtonAndReset(); // Check for premature presses during the countdown
  }

  if (!timeToPress && lives > 0) {
    blinks(CRGB::Red); // All LEDs blink red when time is up
    timeToPress = true;
    pressStartTime = millis();
    Serial.println("Time to press the button!");
  }

  checkButtonAndReset(); // Check for button press during the 5-second window

  delay(10); // Small delay to prevent busy-waiting
}
