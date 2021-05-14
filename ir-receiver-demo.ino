
#define MARK_EXCESS_MICROS    20 // recommended for the cheap VS1838 modules

#include <Arduino.h>
#include <IRremote.h>
#include "PinDefinitionsAndMore.h"


#define BTN_PIN 5

uint16_t sAddress = 0x707;
uint8_t sRepeats = 0;

// pwr btn
uint8_t sCommand = 0x2;

// mute btn 
//uint8_t sCommand = 0xF;


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BTN_PIN, INPUT);

  Serial.begin(115200);
  delay(4000);
  
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  Serial.print(F("Ready to receive IR signals at pin "));
  Serial.println(IR_RECEIVE_PIN);
  
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);
  Serial.print(F("Ready to send IR signals at pin "));
  Serial.println(IR_SEND_PIN);
}


void loop() {
  if (digitalRead(BTN_PIN) == HIGH) {
    IRData IRSendData;
    IRSendData.address = sAddress;
    IRSendData.command = sCommand;
    IRSendData.flags = IRDATA_FLAGS_EMPTY;
  
    IRSendData.protocol = SAMSUNG;
    Serial.print(F("Sending... "));
    Serial.print(F("ADDR=0x"));
    Serial.print(sAddress, HEX);
    Serial.print(F(" CMD=0x"));
    Serial.print(sCommand, HEX);
    Serial.print(F(" via "));
    Serial.println(getProtocolString(IRSendData.protocol));
    IrSender.write(&IRSendData, sRepeats);
    delay(333);
  }
  
  if (IrReceiver.decode()) {  // Grab an IR code
    
    // Check if the buffer overflowed
    if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
      Serial.println("IR code too long. Edit IRremoteInt.h and increase RAW_BUFFER_LENGTH");
      
    } else {
      Serial.println(getProtocolString(IrReceiver.decodedIRData.protocol));
      Serial.println(" =-= ");
      Serial.println(IrReceiver.decodedIRData.address, HEX);
      Serial.println(" =-= ");
      Serial.println(IrReceiver.decodedIRData.command, HEX);
      Serial.println(" =-= ");
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      Serial.println(" =-= ");           
//      Serial.println();
//      IrReceiver.printIRResultShort(&Serial);
      Serial.println();
      Serial.println();
    }
    
    IrReceiver.resume();
  }
}
