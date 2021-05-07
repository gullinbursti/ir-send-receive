
#include <Arduino.h>

#define IR_INPUT_PIN 2
#define LED_PIN 6
#define SPK_PIN 11

#include "TinyIRReceiver.cpp.h"


// Helper macro for getting a macro definition as string
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)


byte ledBrite = 255;


void setup() {
  Serial.begin(115200);
  pinMode(SPK_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.println(F("START " __FILE__ " from " __DATE__));
  initPCIInterruptForTinyReceiver();
  Serial.println(F("Ready to receive NEC IR signals at pin " STR(IR_INPUT_PIN)));
}

void loop() {
  /*
   * Put your code here
   */
}

void handleReceivedTinyIRData(uint16_t aAddress, uint8_t aCommand, bool isRepeat) {
  Serial.print(F("A=0x"));
  Serial.print(aAddress, HEX);
  Serial.print(F(" C=0x"));
  Serial.print(aCommand, HEX);
  Serial.print(F(" R="));
  Serial.print(isRepeat);
  Serial.println();
}
