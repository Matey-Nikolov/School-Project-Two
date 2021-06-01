#include <LiquidCrystal.h>    // Contains LiquidCrystal Library

#include <FastLED.h>


#define NUM_LEDS 32
#define DATA_PIN 9
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];
CRGB ledColor;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int tempPin = 4;                // define the pin of temperature sensor
float tempVal;                  // define a variable to store temperature value

void setup() {
//////////////////
FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);
Serial.begin(9600);

  //////////////////////////////
  lcd.begin(16, 2);     // set up the LCD's number of columns and rows
  startingAnimation();  // display a dynamic start screen

////////////////////////////////////////////////////////////////////////




while(true){

int numEND = 0;
String command = Serial.readStringUntil('\n');
  
  if(command == "ON" || command == "on")
{
  Serial.println("LED is turned ON");
  LEDBlink();
  numEND++;
}

if(numEND == 1)
  break;


}


//////////////////////////////////////////////////////////////////////////////
}

void loop() {
  tempVal = getTemp();
  
  lcdDisplay();           
  delay(200);


  if (tempVal < 20) {
    for (int whiteLed = 0; whiteLed < tempVal; whiteLed = whiteLed + 1) {
      leds[whiteLed] = CRGB::White;
      FastLED.show();
    }
    for (int whiteLed = tempVal; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      if(whiteLed <= tempVal)
        leds[whiteLed] = CRGB::White;
      else
        leds[whiteLed] = CRGB::Black;
    }
  }

  if (20 < tempVal  && tempVal < 26 ) {
    for (int whiteLed = 0; whiteLed < tempVal; whiteLed = whiteLed + 1) {
      leds[whiteLed] = CRGB::Green;
      FastLED.show();
    }
    for (int whiteLed = tempVal; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      
      if(whiteLed <= tempVal)
        leds[whiteLed] = CRGB::Green;
      else
        leds[whiteLed] = CRGB::Black;
    }
  }

  if (26 < tempVal ) {
    for (int whiteLed = 0; whiteLed < tempVal; whiteLed = whiteLed + 1) {
      leds[whiteLed] = CRGB::Red;
      FastLED.show();
    }
    for (int whiteLed = tempVal; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1) {
      if(whiteLed <= tempVal)
        leds[whiteLed] = CRGB::Red;
      else
        leds[whiteLed] = CRGB::Black;
    }
  }

}

void startingAnimation() {
  for (int RGB1 = 32; RGB1 > 0; RGB1--) {
    leds[RGB1] = CRGB::Black;
    FastLED.show();
  }

  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayRight();
  }
  lcd.print("starting...");
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(300);
  } 
   lcd.clear();
}


// function used by LCD1602 to display time and temperature
void lcdDisplay() {
  lcd.setCursor(0, 0);  // set the cursor to (0,0) (first column,first row).
  lcd.print("TEMP: ");  // display temperature information
  lcd.print(tempVal);
  lcd.print("C");
}

// function used to get temperature
float getTemp() {
  // Convert analog value of tempPin into digital value
  int adcVal = analogRead(tempPin);
  // Calculate voltage
  float v = adcVal * 5.0 / 1024;
  // Calculate resistance value of thermistor
  float Rt = 10 * v / (5 - v);
  // Calculate temperature (Kelvin)
  float tempK = 1 / (log(Rt / 10) / 3950 + 1 / (273.15 + 25));
  // Calculate temperature (Celsius)
  return tempK - 273.15;
}

void LEDBlink(){

    for (int RGB1 = 0; RGB1 < 32; RGB1++) {
      leds[RGB1] = CRGB::Black;
      FastLED.show();
    }
delay(1000);
    for (int RGB1 = 0; RGB1 < 32; RGB1++) {
      leds[RGB1] = CRGB::Purple;
      FastLED.show();
      delay(200);
    }
delay(2000);
    for (int RGB1 = 32; RGB1 > 0; RGB1--) {
      leds[RGB1] = CRGB::Orange;
      FastLED.show();
    }
delay(2000);
}
