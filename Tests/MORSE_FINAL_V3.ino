const int BUTTON_PIN = 23;

int latchPin = 15;      // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 2;      // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 0;
byte LEDS = 0;

int lastButtonState = HIGH;
int buttonState;

unsigned long temper = 0;

unsigned long lastDebounce = 0;
unsigned long debounceDelay = 50;

int john = 9;

void setup() {
 Serial.begin(115200);
 pinMode(BUTTON_PIN, INPUT_PULLUP);
 pinMode(latchPin, OUTPUT);
 pinMode(clockPin, OUTPUT);
 pinMode(dataPin, OUTPUT);
delay(100);

}


void loop() {

int reading = digitalRead(BUTTON_PIN);
 if(reading != lastButtonState){
   lastDebounce = millis();
 }
 if((millis() - lastDebounce) > debounceDelay){
   if(reading != buttonState){
     buttonState = reading;
     if(buttonState == LOW){
john = 1;
temper = millis();
     }
   }
 }
   lastButtonState = reading;





if(john == 1){
// put ts in an if statement
// ** 
if((millis() - temper) < 350){
  LEDS = 255; // dot
  updateShiftRegister();
} else if((millis() - temper) < 700){
LEDS = 0; // pause
updateShiftRegister();
} else if((millis() - temper) < 1050){
  LEDS = 255; // dot
  updateShiftRegister();
} else if((millis() - temper) < 1400){
  LEDS = 0; // end
  updateShiftRegister();
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
  LEDS = 255; // dot
} else if((millis() - temper) < 700){
LEDS = 0; // pause
} else if((millis() - temper) < 1750){
LEDS = 255; // line
} else if((millis() - temper) < 2100){
LEDS = 0; //pause
} else if((millis() - temper) < 2450){
LEDS = 255; // dot
} else if((millis() - temper) < 2800){
LEDS = 0; // pause
} else if((millis() - temper) < 3150){
  LEDS = 255; // dot
} else if((millis() - temper) < 3500){
  LEDS = 0; // end
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
  LEDS = 255; // line
} else if((millis() - temper) < 1400){
  LEDS = 0; // pause
} else if((millis() - temper) < 2450){
  LEDS = 255; // line
} else if((millis() - temper) < 2700){
  LEDS = 0; // pause
} else if((millis() - temper) < 3750){
  LEDS = 255; // line
} else if((millis() - temper) < 4000){
  LEDS = 0; // end
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
  LEDS = 255; // dot
} else if((millis() - temper) < 700){
  LEDS = 0; // pause
} else if((millis() - temper) < 1050){
  LEDS = 255; // dot
} else if((millis() - temper) < 1400){
  LEDS = 0; // pause
} else if((millis() - temper) < 1750){
  LEDS = 255; // dot
} else if((millis() - temper) < 2100){
  LEDS = 0; // pause
} else if((millis() - temper) < 3150){
  LEDS = 255; // line
} else if((millis() - temper) < 3500){
  LEDS = 0; // end
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
  LEDS = 255; // dot
 } else if((millis() - temper) < 700){
  LEDS = 0; // end
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
  LEDS = 255; // dot
} else if((millis() - temper) < 700){
  LEDS = 0; // pause
} else if((millis() - temper) < 1050){
  LEDS = 255; // dot
} else if((millis() - temper) < 1400){
  LEDS = 0; // pause
} else if((millis() - temper) < 2450){
  LEDS = 255; // line
} else if((millis() - temper) < 2800){
  LEDS = 0; // end
} else if((millis() - temper) > 4450){
john = 7;
temper = millis();
}
updateShiftRegister();
}

}

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, LEDS);
   digitalWrite(latchPin, HIGH);
}
