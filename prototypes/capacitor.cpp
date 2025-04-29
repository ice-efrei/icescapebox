#include <FastLED.h>

#define LED_PIN 7
#define BUTTON_PIN 4
#define NUM_LEDS 36  // 3 rangées de 12 LEDs en série

CRGB leds[NUM_LEDS];  // Tableau de LEDs
int lives = 3;
int TIME_TO_PRESS = 0;

void setup() {
  randomSeed(analogRead(0));
  pinMode(BUTTON_PIN, INPUT);
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
}

// Blinking effect
void blinks(CRGB leds[]) {
  CRGB temp[NUM_LEDS];
  for (int i = 0; i < NUM_LEDS; i++) {
    temp[i] = leds[i];
  }
  for (int j = 0; j < 5; j++) {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    delay(200);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = temp[i];
    }
    FastLED.show();
    delay(200);
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

// Fonction de reset via bouton
int reset_LEDS(CRGB leds[], int* lives, int* TIME_TO_PRESS) {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    if (*TIME_TO_PRESS) {
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      FastLED.show();
      *TIME_TO_PRESS = 0;
    } else {
      (*lives)--;
    }
  }
  return *lives;
}

void loop() {
  long timer = random(60 * 1000, 5460 * 1000);
  unsigned long start = millis();

  while (millis() - start < timer) {
    float elapsed = millis() - start;
    float progress = elapsed / timer;

    // Dégradé du vert au rouge
    for (int i = 0; i < 12; i++) {
      if (progress >= (i + 1) / 12.0) {
        uint8_t hue = map(i, 0, 11, 96, 0); // 96=Vert -> 32=Jaune -> 0=Rouge
        CRGB color = CHSV(hue, 255, 255);
        leds[i] = leds[i + 12] = leds[i + 24] = color;
      }
    }

    FastLED.show();
    delay(200);

    if (progress >= 1.0) {
      TIME_TO_PRESS = 1;
      blinks(leds);
      lives = reset_LEDS(leds, &lives, &TIME_TO_PRESS);
    }
  }

  delay(2000);
}
