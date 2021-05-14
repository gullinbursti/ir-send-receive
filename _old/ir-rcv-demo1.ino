
#include <IRremote.h>


const int RECV_PIN = 2;
const int SPK_PIN = 11;
const int LED_PIN = 6;

byte ledBrite = 255;
long prevState = 0x00000000;

IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

//  pinMode(SPK_PIN, OUTPUT);
//  pinMode(LED_PIN, OUTPUT);
}

void loop() {
//  if (irrecv.decode(&results)) {
      if (irrecv.decode()) {
//    Serial.println(results.value, HEX);
//    Serial.println(prevState, HEX);
//    Serial.println(ledBrite);

    // prev btn held dn
    if (results.value == 0xFFFFFFFF) {
      if (prevState == 0xFFA857) {
        ledBrite = min(ledBrite + 8 + ((255 - ledBrite) * 0.225), 255);
//        analogWrite(LED_PIN, ledBrite);
      
      } else if (prevState == 0xFFE01F) {
        ledBrite = max(0, ledBrite - 8 - ((255 - ledBrite) * 0.125));
//        analogWrite(LED_PIN, ledBrite);
      
    // home / eq btn
    } else if ((results.value == 0x5743C03F || results.value == 0xFF906F) && (ledBrite == 255)) { 
      
    }
    
    // */ CH btn
    } else if (results.value == 0x57438679 || results.value == 0xFF629D) {
//      analogWrite(SPK_PIN, 50);
      delay(25);
//      analogWrite(SPK_PIN, 0);
      

    // home / eq btn
    } else if (results.value == 0x5743C03F || results.value == 0xFF906F) {
      if (digitalRead(LED_PIN) > 0) {
        ledBrite = 0;
//        analogWrite(LED_PIN, ledBrite);

      } else {
        ledBrite = 255;
//        analogWrite(LED_PIN, ledBrite);
      }

    // */ CH btn
    } else if (results.value == 0x57438679 || results.value == 0xFF629D) {
      analogWrite(SPK_PIN, 33);
      delay(33);
      analogWrite(SPK_PIN, 0);

    // vol dn
    } else if (results.value == 0xFFE01F) {
      ledBrite = max(0, ledBrite - 8 - ((255 - ledBrite) * 0.125));
//      analogWrite(LED_PIN, ledBrite);

    // vol up
    } else if (results.value == 0xFFA857) {
      ledBrite = min(ledBrite + 8 + ((255 - ledBrite) * 0.225), 255);
//      analogWrite(LED_PIN, ledBrite);
    }

    if (results.value == 0xFFFFFFFF) {
      if (prevState == 0xFFA857) {
        ledBrite = min(ledBrite + 8, 255);
//        analogWrite(LED_PIN, ledBrite);
      
      } else if (prevState == 0xFFE01F) {
        ledBrite = max(0, ledBrite - 8);
//        analogWrite(LED_PIN, ledBrite);
      }
    
    } else {
      prevState = results.value;
    }
    
    irrecv.resume();
  }
}
