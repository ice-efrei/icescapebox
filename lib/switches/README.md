# Switches

This library is designed to manage a set of switches and LEDs, including a rotary encoder for generating random logic mappings. The primary functionality includes reading switch states, updating LED states based on XOR logic, and checking for a win condition.

## Pin Definitions

- `switchPins[5]`: An array of integers representing the pin numbers for the switches.
- `ledPins[5]`: An array of integers representing the pin numbers for the LEDs.
- `encoderPinA`: The pin number for the rotary encoder's A pin.
- `encoderPinB`: The pin number for the rotary encoder's B pin.

## Game Variables

- `ledStates[5]`: An array of integers representing the states of the LEDs (0 for OFF, 1 for ON).
- `switchStates[5]`: An array of integers representing the states of the switches (0 for OFF, 1 for ON).
- `switchToLED[5][5]`: A 5x5 matrix representing the mapping between switches and LEDs. Each element can be 0 (no effect) or 1 (XOR effect).
- `encoderValue`: An integer representing the current value of the rotary encoder.
- `lastEncoderValue`: An integer representing the last read value of the rotary encoder.

## Functions

### `bool applyXOR(bool ledState, bool switchState)`

Applies an XOR logic gate to the given LED and switch states.

- `ledState`: The current state of the LED.
- `switchState`: The current state of the switch.
- Returns: The result of the XOR operation.

### `void generateMatrix(int seed)`

Generates a random 5x5 matrix based on the provided seed.

- `seed`: An integer seed for the random number generator.

### `void readEncoder()`

Reads the rotary encoder and updates the `encoderValue`. Currently, this function is a placeholder and sets `encoderValue` to 0.

### `void updateLEDs()`

Reads the states of the switches and updates the states of the LEDs based on the switch-to-LED matrix and XOR logic. Includes debounce logic to ensure stable switch readings.

### `bool checkWinCondition()`

Checks if all LEDs are in the ON state, indicating a win condition.

- Returns: `true` if all LEDs are ON, `false` otherwise.

