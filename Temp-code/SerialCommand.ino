void setup() {
  Serial.begin(9600);
}

void loop() {
Commands();
}

void Commands(){
  
  if(Serial.available()) // if there is data comming
  {
    String command = Serial.readStringUntil('\n'); // read string until meet newline character

    if(command == "ON" || command == "on")
    {
      digitalWrite(LED_BUILTIN, HIGH); // turn on LED
      Serial.println("LED is turned ON"); // send action to Serial Monitor
    }
    else
    if(command == "OFF" || command == "off")
    {
      digitalWrite(LED_BUILTIN, LOW);  // turn off LED
      Serial.println("LED is turned OFF"); // send action to Serial Monitor
    }
  }
}
