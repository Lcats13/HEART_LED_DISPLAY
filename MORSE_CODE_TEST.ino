// 1. Dots are 200, dashes are 600, pause between = 200, pause between letters = 1000;
enum State {
  STATE_WAIT,
 STATE_LETTERI,
 STATE_LETTERL,
 STATE_LETTERO,
  STATE_LETTERV,
 STATE_LETTERE,
 STATE_LETTERU

};
const int BUTTON_PIN = 23;
const int LED_PIN = 22;
unsigned long lastBlink = 0;
unsigned long blinkDelay = 500;

int latchPin = 15;      // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 2;      // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 0;
unsigned long oneLastShift = 0;
int FirstShift = 0;
byte LEDS = 0;

int ledState = LOW;
int lastButtonState = HIGH;
int buttonState;

unsigned long temper = 0;

bool FullSend = false;

unsigned long lastDebounce = 0;
unsigned long debounceDelay = 50;


// Initialize the starting state
State currentState = STATE_WAIT;
unsigned long lastStateChange = 0;
const unsigned long interval = 2000; // Change state every 2 seconds


void setup() {
 Serial.begin(115200);
 Serial.println("State Machine Initialized...");
 pinMode(BUTTON_PIN, INPUT_PULLUP);
 pinMode(LED_PIN, OUTPUT);
 pinMode(latchPin, OUTPUT);
 pinMode(clockPin, OUTPUT);
 pinMode(dataPin, OUTPUT);


}


void loop() {
 // 2. The State Machine Logic
 switch (currentState) {
case STATE_WAIT:
handleWait();
break;

   case STATE_LETTERI:
     handleLetterI();
     break;


   case STATE_LETTERL:
     handleLetterL();
     break;


   case STATE_LETTERO:
     handleLetterO();
     break;

    case STATE_LETTERV:
     handleLetterV();
     break;

    case STATE_LETTERE:
     handleLetterE();
     break;

    case STATE_LETTERU:
     handleLetterU();
     break;
 }
/////debounce time:
int reading = digitalRead(BUTTON_PIN);




 // 3. Logic to trigger state changes (simulated by a timer)
 




 if(reading != lastButtonState){
   lastDebounce = millis();
 }
 if((millis() - lastDebounce) > debounceDelay){
   if(reading != buttonState){
     buttonState = reading;
     if(buttonState == LOW){
transitionToMorseState();
temper = millis();
     }
   }
 }
   lastButtonState = reading;

}


// --- State Handler Functions ---


void handleWait() {
 LEDS = 0;
updateShiftRegister();

}



void handleLetterI() {
  // I = * *
if((millis() - temper) > 0 && (millis() - temper) < 350){
  LEDS = 255; // dot
  updateShiftRegister();
}
updateShiftRegister();
if ((millis() - temper) > 350 && (millis() - temper) < 700){
  LEDS = 0; // pause
   updateShiftRegister();
}
if((millis() - temper) > 700 && (millis() - temper) < 1050){
LEDS = 255; // dot
  updateShiftRegister();
}
  if ((millis() - temper) > 1050){
  LEDS = 0; // end
   updateShiftRegister();
  }
  if((millis() - temper) > 3050){
    temper = millis(); // end
    transitionToMorseState();
  }
}


void handleLetterL() {
  // * -- **
if((millis() - temper) > 0 && (millis() - temper) < 350){
  LEDS = 255; // dot
  updateShiftRegister();
}
if((millis() - temper) > 350 && (millis() - temper) < 700){
  LEDS = 0; // pause
  updateShiftRegister();
}
if((millis() - temper) > 700 && (millis() - temper) < 1750){
  LEDS = 255; // line
  updateShiftRegister();
}
if((millis() - temper) > 1750 && (millis() - temper) < 2100){
  LEDS = 0; // pause
  updateShiftRegister();
}
if((millis() - temper) > 2100 && (millis() - temper) < 2450){
  LEDS = 255; // dot
  updateShiftRegister();
}
if((millis() - temper) > 2450 && (millis() - temper) < 2800){
  LEDS = 0; // pause
  updateShiftRegister();
}
if((millis() - temper) > 2800 && (millis() - temper) < 3150){
  LEDS = 255; // dot
  updateShiftRegister();
}
  if((millis() - temper) > 3150){
  LEDS = 0; // end
  updateShiftRegister();
}

if((millis() - temper) > 5150){
  LEDS = 0; // pause before transition
  updateShiftRegister();
  temper = millis();
  transitionToMorseState();
}
}

void handleLetterO() {
  // -- -- -- 
 if((millis() - temper) > 0 && (millis() - temper) < 1050){
  LEDS = 255; // line
  updateShiftRegister();
}
if((millis() - temper) > 1050 && (millis() - temper) < 1400){
  LEDS = 0; // Pause
  updateShiftRegister();
}
if((millis() - temper) > 1400 && (millis() - temper) < 2450){
  LEDS = 255; // line
  updateShiftRegister();
}
if((millis() - temper) > 2450 && (millis() - temper) < 2800){
  LEDS = 0; // Pause
  updateShiftRegister();
}
if((millis() - temper) > 2800 && (millis() - temper) < 3850){
  LEDS = 255; // line
  updateShiftRegister();
}
if((millis() - temper) > 3850){
  LEDS = 0; // end
  updateShiftRegister();
}
if((millis() - temper) > 5900){
  LEDS = 0; // end
  updateShiftRegister();
  temper = millis();
  transitionToMorseState();
}
}
void handleLetterV() {
 // * * * --
if((millis() - temper) > 0 && (millis() - temper) < 350){
  LEDS = 255; // dot
  updateShiftRegister();
}
if((millis() - temper) > 350 && (millis() - temper) < 700){
  LEDS = 0; // pause
  updateShiftRegister();
}
if((millis() - temper) > 700 && (millis() - temper) < 1050){
  LEDS = 255; // dot
  updateShiftRegister();
}
if((millis() - temper) > 1050 && (millis() - temper) < 1400){
  LEDS = 0; // pause
  updateShiftRegister();
}
if((millis() - temper) > 1400 && (millis() - temper) < 1750){
  LEDS = 255; // dot
  updateShiftRegister();
}
if((millis() - temper) > 1750 && (millis() - temper) < 2100){
  LEDS = 0; // pause
  updateShiftRegister();
}
if((millis() - temper) > 2100 && (millis() - temper) < 3150){
  LEDS = 255; // line
  updateShiftRegister();
}
if((millis() - temper) > 3150){
  LEDS = 0; // end
  updateShiftRegister();
}
if((millis() - temper) > 5200){
  LEDS = 0; // end
  updateShiftRegister();
  temper = millis();
  transitionToMorseState();
}
}
void handleLetterE() {
// *
 if((millis() - temper) > 0 && (millis() - temper) < 350){
  LEDS = 255; // pause
  updateShiftRegister();
}
if((millis() - temper) > 350){
  LEDS = 0; // pause
  updateShiftRegister();
}
if((millis() - temper) > 2400){
  LEDS = 0; // end
  updateShiftRegister();
  temper = millis();
  transitionToMorseState();
}
}

void handleLetterU() {
 // * * --
 if((millis() - temper) > 0 && (millis() - temper) < 350){
  LEDS = 255; // dot
  updateShiftRegister();
}
if((millis() - temper) > 350 && (millis() - temper) < 700){
  LEDS = 0; // pause
  updateShiftRegister();
}
 if((millis() - temper) > 700 && (millis() - temper) < 1050){
  LEDS = 255; // dot
  updateShiftRegister();
}
 if((millis() - temper) > 1050 && (millis() - temper) < 1400){
  LEDS = 0; // pause
  updateShiftRegister();
}
if((millis() - temper) > 1400 && (millis() - temper) < 2450){
  LEDS = 255; // line
  updateShiftRegister();
}
if((millis() - temper) > 2450){
  LEDS = 0; // end
  updateShiftRegister();
}
if((millis() - temper) > 2450){
  LEDS = 0; // end
  updateShiftRegister();
  transitionToMorseState();
}
}




// --- Simple Transition Logic ---


void transitionToMorseState() {
 switch (currentState) {
    case STATE_WAIT:      currentState = STATE_LETTERI;       break;
   case STATE_LETTERI:       currentState = STATE_LETTERL; break;
   case STATE_LETTERL: currentState = STATE_LETTERO;      break;
   case STATE_LETTERO:      currentState = STATE_LETTERV;       break;
   case STATE_LETTERV:      currentState = STATE_LETTERE;       break;
   case STATE_LETTERE:      currentState = STATE_LETTERU;       break;
   case STATE_LETTERU:      currentState = STATE_WAIT;       break;
;
 }
  Serial.print("Transitioned to state: ");
 Serial.println(currentState); // Prints the enum index
}

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, LEDS);
   digitalWrite(latchPin, HIGH);
}
