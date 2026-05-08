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

const int MORSE_BUTTON_PIN = 22;
const int buttonPin = 23;
const int firstLatchPin = 19;
const int firstClockPin = 18;
const int firstDataPin = 5;
const int secondLatchPin = 16;
const int secondClockPin = 17;
const int secondDataPin = 15;

byte FIRST_LEDS = 0;
byte SECOND_LEDS = 0;

unsigned long display = 0;


unsigned long lastDebounce = 0;
unsigned long debounceDelay = 50;

unsigned long lastMorseDebounce = 0;
unsigned long morseDebounceDelay = 50;

unsigned long oneLastShift = 0;
int FirstShift = 0;

unsigned long twoLastShift = 0;
int SecondShift = 0;

int lastButtonState = HIGH;
int buttonState;

int lastMorseState = HIGH;
int morseState;

unsigned long temper = 0;

state currentState = STATE_FIRSTLINEAR;

int john = 9;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
   pinMode(MORSE_BUTTON_PIN, INPUT_PULLUP);
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

int readingMorse = digitalRead(MORSE_BUTTON_PIN);
int reading = digitalRead(buttonPin);

// first button(display)
if(reading != lastButtonState){
  lastDebounce = millis();
}
if((millis() - lastDebounce) > debounceDelay){
  if (reading != buttonState){
    buttonState = reading;
    if(buttonState == LOW){
      john = 10;
      TransitionToNextState();
      Serial.println("displayPressed!");
    }
  }
}
//second button(morse)
 if(readingMorse != lastMorseState){
   lastMorseDebounce = millis();
 }
 if((millis() - lastMorseDebounce) > morseDebounceDelay){
   if(readingMorse != morseState){
     morseState = readingMorse;
     if(morseState == LOW){
john = 1;
currentState = STATE_REST;
temper = millis();
Serial.println("morsePresssed!");

     }
   }
 }
 //end
  lastMorseState = readingMorse;
lastButtonState = reading;

//Morse logic(Stays in the loop like a G)
if(john == 1){
// put ts in an if statement
// ** 
if((millis() - temper) < 350){
  FIRST_LEDS = 0; // tuff
  SECOND_LEDS = 0;
} else if((millis() - temper) < 700){
 FIRST_LEDS = 255;
SECOND_LEDS = 255; // dot
} else if((millis() - temper) < 1050){
  FIRST_LEDS = 0;
SECOND_LEDS = 0; // pause
} else if((millis() - temper) < 1400){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 1750){
FIRST_LEDS = 0;
SECOND_LEDS = 0; // end
} else if((millis() - temper) > 3400){
      john = 2;
temper = millis(); // end
}
 updateShiftRegister();
}


if (john == 2){
// * -- * *
//put ts in an if statement

if((millis() - temper) < 350){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 700){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 1750){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// line
} else if((millis() - temper) < 2100){
FIRST_LEDS = 0;
SECOND_LEDS = 0;//pause
} else if((millis() - temper) < 2450){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 2800){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 3150){
  FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 3500){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// end
} else if((millis() - temper) > 5150){
  john = 3; // end
  temper = millis();
}
updateShiftRegister();
}

if(john == 3){
 
  // -- -- --
//put ts in an if statement
if((millis() - temper) < 1050){
  FIRST_LEDS = 255;
SECOND_LEDS = 255;// line
} else if((millis() - temper) < 1400){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 2450){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// line
} else if((millis() - temper) < 2700){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 3750){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// line
} else if((millis() - temper) < 4000){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// end
} else if((millis() - temper) > 5750){
john = 4;
temper = millis();
}
updateShiftRegister();
}

if(john == 4){

  // * * * --
//put ts in an if statement

if((millis() - temper) < 350){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 700){
 FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 1050){
  FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 1400){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 1750){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 2100){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 3150){
   FIRST_LEDS = 255;
SECOND_LEDS = 255;// line
} else if((millis() - temper) < 3500){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// end
} else if((millis() - temper) > 5150){
  john = 5;
  temper = millis();
}
updateShiftRegister();
}




if(john == 5){
  // *
// put ts in an if statement
 if((millis() - temper) < 350){
  FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
 } else if((millis() - temper) < 700){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// end
 } else if((millis() - temper) > 2350){
  john = 6;
  temper = millis();
 }
updateShiftRegister();
}


if(john == 6){

  // * * --
// put ts in an if statement
if((millis() - temper) < 350){
  FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 700){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 1050){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 1400){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// pause
} else if((millis() - temper) < 2450){
  FIRST_LEDS = 255;
SECOND_LEDS = 255;// line
} else if((millis() - temper) < 2800){
FIRST_LEDS = 0;
SECOND_LEDS = 0;// end
} else if((millis() - temper) > 4450){
john = 7;
temper = millis();
}
updateShiftRegister();
}
// end morse logic(stayed in the loop like a G)

}
void handleRest(){


}

void handleFirstLinear(){
if(john = 10){
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
    display = millis();
  }

  }
   if(FirstShift == 8 && SecondShift == 8){
     if((millis() - display) > 250){
    TransitionToNextState();
     }
}
} else{
  TransitionToNextState();
}
}
void handleReset(){
  if(john = 10){
  SECOND_LEDS = 0;
  SecondShift = 0;
 FIRST_LEDS = 0;
    FirstShift = 0;
    updateShiftRegister();
    TransitionToNextState();
  }else{
  TransitionToNextState();
}
}

void handleSecondLinear(){
  if(john = 10){
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
    display = millis();
  }

  }
   if(FirstShift == 8 && SecondShift == 8){
  if((millis() - display) > 250){
    TransitionToNextState();
    display = millis();
     }
}
}else{
  TransitionToNextState();
}
}
void handleSecondReset(){
  if(john = 10){
FIRST_LEDS = 0;
SECOND_LEDS = 0;
updateShiftRegister();
if((millis() - display) > 350){
TransitionToNextState();
display = millis();
}
}else{
  TransitionToNextState();
}
}
void handleFirstSolid(){
  if(john = 10){
  FIRST_LEDS = 255;
SECOND_LEDS = 255;
updateShiftRegister();
if((millis() - display) > 350){
TransitionToNextState();
display = millis();
}
  }else{
  TransitionToNextState();
}
}

void handleThirdReset(){
  if(john = 10){
FIRST_LEDS = 0;
SECOND_LEDS = 0;
updateShiftRegister();
if((millis() - display) > 350){
TransitionToNextState();
display = millis();
}
}else{
  TransitionToNextState();
}
}
void handleSecondSolid(){
  if(john = 10){
 FIRST_LEDS = 255;
SECOND_LEDS = 255;
updateShiftRegister();
  }else{
  TransitionToNextState();
}
  if((millis() - display) > 350){
TransitionToNextState();
display = millis();
}
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
