/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Fade
*/

int buz = PIN_PA4;           // the PWM pin the LED is attached to
int but1 = PIN_PC0;           // the PWM pin the LED is attached to

int buttonState = 0; 

int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 9 to be an output:
  pinMode(buz, OUTPUT);
  pinConfigure(PIN_PC0,(PIN_DIR_INPUT | PIN_PULLUP_ON));
  digitalWrite(buz, HIGH);
  delay(100);
  digitalWrite(buz, LOW);
  delay(100);
  digitalWrite(buz, HIGH);
  delay(100);
  digitalWrite(buz, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  buttonState = digitalRead(but1);
  if (buttonState == LOW) {
    // turn LED on:
    digitalWrite(buz, HIGH);
  } else {
    // turn LED off:
    digitalWrite(buz, LOW);
  }
}
