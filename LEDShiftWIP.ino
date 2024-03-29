#define P_SERIAL 5   //pin 14 on the 75HC595 serial/data
#define P_LATCH  6   //pin 12 on the 75HC595 latch
#define P_CLOCK  7   //pin 11 on the 75HC595 clock

// Number of shift registers
#define REGISTERS 6

// Total number of pins
#define PINS REGISTERS * 8

// Will point to our light patterns. A byte is an 8-bit BINARY variable to match the 8 lights
byte * registerPatterns;

// This is only to deminstrate how to cycle through all the pins, start at 0 and go to 15
int cycle = 0;

void setup() {

  // Create an array of bytes to match the number of registeres (1 pattern for each)
  registerPatterns = new byte[REGISTERS];

  // Start with all the lights off
  clearRegisters();

  // Opent the ports
  pinMode(P_SERIAL, OUTPUT);
  pinMode(P_LATCH, OUTPUT);
  pinMode(P_CLOCK, OUTPUT);

  // Setup the serial output for testing values
  Serial.begin(9600);
}

void clearRegisters() {

  // For each register, set it's pattern to 0 (which, rember is 00000000 in bytes, meaning all lights off)
  for (size_t i = 0; i < REGISTERS; i++) {
    registerPatterns[i] = 0;
  }
}

// Takes the overall pin number and figures out which register it's on and what pin it would be on that register
void writePinToByte(int pin, bool state) {
  // Which register are we looking at? 0=first, 1=second, etc. "/" will round down to an int
  int r = pin / 8;

  // Which pin on that register, finding the remainder of the pin division will give us 0-7
  int q = pin % 8;

  // Go through each of our stored patterns and write them back to the registers in order
  for (size_t i = 0; i < REGISTERS; i++) {

    // Point to the current pattern for this register
    byte * pattern = &registerPatterns[i];

    // If this is the register that the pin we are editing is on...
    if (i == r) {
      // Take the "pattern" that holds the 8 bits, change the binary digit at position "q" (0-7) to "state" (LOW = 0, HIGH = 1)
      bitWrite(*pattern, q, state);
    }

  }
}

void writeToRegisters() {

  // Lock the registers to ready them to be written
  digitalWrite(P_LATCH, LOW);

  // Go through each of our stored patterns and write them back to the registers in order
  for (size_t i = 0; i < REGISTERS; i++) {

    // Point to the current pattern for this register
    byte * pattern = &registerPatterns[i];

    // Write the pattern back to the register chips byte by byte
    shiftOut(P_SERIAL, P_CLOCK, MSBFIRST, *pattern);

    // Activate to show the byte pattern as a decimal number
    //Serial.println(*pattern);

    // Activate to show the byte pattern as a binary number
    //Serial.println(*pattern, BIN);
  }

  // Unlock the registers
  digitalWrite(P_LATCH, HIGH);
}

void loop() {

  // WORKING EXAMPLE
  // To test our registers, let's stream a single light across the board one by one in a loop

  // Clear all pins with each loop
  clearRegisters();

  // Write one pin, then cycle it up for the next run
  writePinToByte(cycle++, HIGH);

  // Write to the registers
  writeToRegisters();

  // Reset the light back to the 0 pin once it hits the end
  if (cycle >= PINS) {
    cycle = 0;
  }

  // Put a small pause between lights
  delay(500);
}
