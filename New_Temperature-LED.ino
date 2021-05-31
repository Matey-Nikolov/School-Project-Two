#include <LiquidCrystal.h>    // Contains LiquidCrystal Library
#include <FlexiTimer2.h>      // Contains FlexiTimer2 Library


#include <FastLED.h>


#define NUM_LEDS 32
#define DATA_PIN 9
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];
CRGB ledColor;
//

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int tempPin = 4;                // define the pin of temperature sensor
float tempVal;                  // define a variable to store temperature value
int hour, minute, second;       // define variables stored record time

void setup() {
  lcd.begin(16, 2);     // set up the LCD's number of columns and rows
  startingAnimation();  // display a dynamic start screen

////////////////////////////////////////////////////////////////////////
 FastLED.addLeds<WS2801, DATA_PIN, CLOCK_PIN, RGB>(leds, NUM_LEDS);


  
    for (int RGB1 = 0; RGB1 < 32; RGB1++) {
      leds[RGB1] = CRGB::Black;
      FastLED.show();
    }
delay(1000);
    for (int RGB1 = 0; RGB1 < 32; RGB1++) {
      leds[RGB1] = CRGB::Purple;
      FastLED.show();
    }
delay(1000);
//////////////////////////////////////////////////////////////////////////////
  FlexiTimer2::set(1000, timerInt);  // configure the timer and interrupt function
  FlexiTimer2::start();              // start timer
  Serial.begin(9600);                // initialize serial port with baud rate 9600
  Serial.println("UNO is ready!");   // print the string "UNO is ready!"
  Serial.println("Input hour,minute,second to set time.");
}

void loop() {
  // Get temperature
  tempVal = getTemp();
  if (second >= 60) {       // when seconds is equal to 60, minutes plus 1
    second = 0;
    minute++;
    if (minute >= 60) {     // when minutes is equal to 60, hours plus 1
      minute = 0;
      hour++;
      if (hour >= 24) {     // when hours is equal to 24, hours turn to zero
        hour = 0;
      }
    }
  }
  lcdDisplay();             // display temperature and time information on LCD
  delay(200);

  if (tempVal < 20) {
    for (int whiteLed = 0; whiteLed < tempVal; whiteLed = whiteLed + 1) {
      leds[whiteLed] = CRGB::White;
      FastLED.show();
//      delay(100);
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
//      delay(100);
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
//      delay(100);
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

// the timer interrupt function of FlexiTimer2 is executed every 1s
void timerInt() {
  second++;       // second plus 1
}

// serial port interrupt function
void serialEvent() {
  int inInt[3];  // define an array to save the received serial data
  while (Serial.available()) {
    for (int i = 0; i < 3; i++) {
      inInt[i] = Serial.parseInt();  // receive 3 integer data
    }
    // print the received data for confirmation
    Serial.print("Your input is: ");
    Serial.print(inInt[0]);
    Serial.print(", ");
    Serial.print(inInt[1]);
    Serial.print(", ");
    Serial.println(inInt[2]);
    // use received data to adjust time
    hour = inInt[0];
    minute = inInt[1];
    second = inInt[2];
    // print the modified time
    Serial.print("Time now is: ");
    Serial.print(hour / 10);
    Serial.print(hour % 10);
    Serial.print(':');
    Serial.print(minute / 10);
    Serial.print(minute % 10);
    Serial.print(':');
    Serial.print(second / 10);
    Serial.println(second % 10);
  }
}

// function used by LCD1602 to display time and temperature
void lcdDisplay() {
  lcd.setCursor(0, 0);  // set the cursor to (0,0) (first column,first row).
  lcd.print("TEMP: ");  // display temperature information
  lcd.print(tempVal);
  lcd.print("C");
  lcd.setCursor(0, 1);  // set the cursor to (0,1) (first column,second row)
  lcd.print("TIME: ");  // display time information
  lcd.print(hour / 10);
  lcd.print(hour % 10);
  lcd.print(':');
  lcd.print(minute / 10);
  lcd.print(minute % 10);
  lcd.print(':');
  lcd.print(second / 10);
  lcd.print(second % 10);
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
