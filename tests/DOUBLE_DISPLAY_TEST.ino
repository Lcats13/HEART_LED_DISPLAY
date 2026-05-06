enum state {
STATE_REST,
STATE_FIRSTLINEAR,
STATE_RESET,
STATE_SECONDLINEAR,
STATE_SECONDRESET,
STATE_FIRSTSOLID,
STATE_THIRDRESET,
STATE_SECONDSOLID,
};


const int buttonPin = 23;
const int firstLatchPin = 19;
const int firstClockPin = 18;
const int firstDataPin = 5;
const int secondLatchPin = 16;
const int secondClockPin = 17;
const int secondDataPin = 15;

byte FIRST_LEDS = 0;
byte SECOND_LEDS = 0;

unsigned long lastBlink = 0;
unsigned long blinkDelay = 500;

unsigned long lastDebounce = 0;
unsigned long debounceDelay = 50;

unsigned long oneLastShift = 0;
int FirstShift = 0;

unsigned long twoLastShift = 0;
int SecondShift = 0;

int lastButtonState = HIGH;
int buttonState;
int ledState = LOW;

state currentState = STATE_REST;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(firstLatchPin, OUTPUT);
  pinMode(firstClockPin, OUTPUT);
  pinMode(firstDataPin, OUTPUT);
  pinMode(secondLatchPin, OUTPUT);
  pinMode(secondClockPin, OUTPUT);
  pinMode(secondDataPin, OUTPUT);
}

void loop() {
 switch (currentState){
  case STATE_REST:
  handleRest();
  break;
 

 case STATE_FIRSTLINEAR:
 handleFirstLinear();
 break;

 case STATE_RESET:
  handleReset();
  break;

  case STATE_SECONDLINEAR:
 handleSecondLinear();
 break;

 case STATE_SECONDRESET:
 handleSecondReset();
 break;

 case STATE_FIRSTSOLID:
 handleFirstSolid();
 break;

 case STATE_THIRDRESET:
 handleThirdReset();
 break;

 case STATE_SECONDSOLID:
 handleSecondSolid();
 break;
 }

int reading = digitalRead(buttonPin);

if(reading != lastButtonState){
  lastDebounce = millis();
}
if((millis() - lastDebounce) > debounceDelay){
  if (reading != buttonState){
    buttonState = reading;
    if(buttonState == LOW){
      TransitionToNextState();
    }
  }
}
lastButtonState = reading;
}
void handleRest(){
FIRST_LEDS = 0;
SECOND_LEDS = 0;
updateShiftRegister();


}

void handleFirstLinear(){

if((millis() - oneLastShift) > 150){
  oneLastShift = millis();
  if(FirstShift < 8){
    bitSet(FIRST_LEDS, FirstShift);
    updateShiftRegister();
    FirstShift ++;
  } else{
    FIRST_LEDS = 0;
    FirstShift = 0;
    updateShiftRegister();
  }
}
 
  
  if((millis() - twoLastShift) > 150){
  twoLastShift = millis();
  if(SecondShift < 8){
    bitSet(SECOND_LEDS, SecondShift);
    updateShiftRegister();
    SecondShift ++;
  } else{
    SECOND_LEDS = 0;
    SecondShift = 0;
    updateShiftRegister();
  }

  }
   if(FirstShift == 8 && SecondShift == 8){
     delay(250);
    TransitionToNextState();

}
}
void handleReset(){
  SECOND_LEDS = 0;
  SecondShift = 0;
 FIRST_LEDS = 0;
    FirstShift = 0;
    updateShiftRegister();
    TransitionToNextState();
}

void handleSecondLinear(){
if((millis() - oneLastShift) > 150){
  oneLastShift = millis();
  if(FirstShift < 8){
    bitSet(FIRST_LEDS, FirstShift);
    updateShiftRegister();
    FirstShift ++;
  } else{
    FIRST_LEDS = 0;
    FirstShift = 0;
    updateShiftRegister();
  }

  }

if((millis() - twoLastShift) > 150){
  twoLastShift = millis();
  if(SecondShift < 8){
    bitSet(SECOND_LEDS, SecondShift);
    updateShiftRegister();
    SecondShift ++;
  } else{
    SECOND_LEDS = 0;
    SecondShift = 0;
    updateShiftRegister();
  }

  }
   if(FirstShift == 8 && SecondShift == 8){
     delay(250);
    TransitionToNextState();
}
}
void handleSecondReset(){
FIRST_LEDS = 0;
SECOND_LEDS = 0;
updateShiftRegister();
delay(350);
TransitionToNextState();
}

void handleFirstSolid(){
  FIRST_LEDS = 255;
SECOND_LEDS = 255;
updateShiftRegister();
delay(350);
TransitionToNextState();
}

void handleThirdReset(){
FIRST_LEDS = 0;
SECOND_LEDS = 0;
updateShiftRegister();
delay(350);
TransitionToNextState();
}
void handleSecondSolid(){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;
updateShiftRegister();
}

void updateShiftRegister(){
  digitalWrite(firstLatchPin, LOW);
  shiftOut(firstDataPin, firstClockPin, MSBFIRST, FIRST_LEDS);
  digitalWrite(firstLatchPin, HIGH);
  digitalWrite(secondLatchPin, LOW);
  shiftOut(secondDataPin, secondClockPin, MSBFIRST, SECOND_LEDS);
  digitalWrite(secondLatchPin, HIGH);
}

void TransitionToNextState(){
  switch (currentState) {
    case STATE_REST: currentState = STATE_FIRSTLINEAR; break;
    case STATE_FIRSTLINEAR: currentState = STATE_RESET; break;
    case STATE_RESET: currentState = STATE_SECONDLINEAR; break;
    case STATE_SECONDLINEAR: currentState = STATE_SECONDRESET; break; 
     case STATE_SECONDRESET: currentState = STATE_FIRSTSOLID; break;
      case STATE_FIRSTSOLID: currentState = STATE_THIRDRESET; break;
      case STATE_THIRDRESET: currentState = STATE_SECONDSOLID; break;
      case STATE_SECONDSOLID: currentState = STATE_REST; break;
  }
   Serial.print("Transitioned to state: ");
 Serial.println(currentState); // Prints the enum index
}
