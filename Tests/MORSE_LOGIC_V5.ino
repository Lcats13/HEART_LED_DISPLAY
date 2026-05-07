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

int lastMorseState = HIGH;
int morseState;

unsigned long temper = 0;

unsigned long lastMorseDebounce = 0;
unsigned long morseDebounceDelay = 50;

int john = 9;

void setup() {
 Serial.begin(115200);
 pinMode(MORSE_BUTTON_PIN, INPUT_PULLUP);
 pinMode(morseLatchPin, OUTPUT);
 pinMode(morseClockPin, OUTPUT);
 pinMode(morseDataPin, OUTPUT);
delay(100);

}


void loop() {

int readingMorse = digitalRead(MORSE_BUTTON_PIN);
 if(readingMorse != lastMorseState){
   lastMorseDebounce = millis();
 }
 if((millis() - lastMorseDebounce) > morseDebounceDelay){
   if(readingMorse != morseState){
     morseState = readingMorse;
     if(morseState == LOW){
john = 1;
temper = millis();
     }
   }
 }
   lastMorseState = readingMorse;





if(john == 1){
// put ts in an if statement
// ** 
if((millis() - temper) < 350){
FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 700){
  FIRST_LEDS = 0;
SECOND_LEDS = 0; // pause
} else if((millis() - temper) < 1050){
FIRST_LEDS = 255;
SECOND_LEDS = 255;// dot
} else if((millis() - temper) < 1400){
FIRST_LEDS = 0;
SECOND_LEDS = 0; // end
} else if((millis() - temper) > 3050){
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
SECOND_LEDS = 255; // dot
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

}

void updateShiftRegister(){
  digitalWrite(firstLatchPin, LOW);
  shiftOut(firstDataPin, firstClockPin, MSBFIRST, FIRST_LEDS);
  digitalWrite(firstLatchPin, HIGH);
  digitalWrite(secondLatchPin, LOW);
  shiftOut(secondDataPin, secondClockPin, MSBFIRST, SECOND_LEDS);
  digitalWrite(secondLatchPin, HIGH);
}
