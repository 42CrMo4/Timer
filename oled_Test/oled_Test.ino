// Test U8X8 OLED
// MegaTinyCore 2.3.2
//   Chip: ATtiny1624
//   Clock: 10MHz
//   millis()/micros() TCB1
//   Voltage for UART: Closer to 3V
//   Startup Time: 8mS

#include <U8x8lib.h> // https://github.com/olikraus/u8g2  v2.28.10

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

//int pinLED1 = PIN_PA6;
int counter = 0;

void setup() {
  delay(500);
//  pinMode(pinLED1, OUTPUT);
//  digitalWrite(pinLED1,LOW);
//  Serial.begin(115200);
//  Serial.print("Test");
  delay(100);
  u8x8.begin();
  u8x8.setFlipMode(0);
  u8x8.setFont(u8x8_font_courB24_3x4_n);
//  digitalWrite(pinLED1,HIGH);    
}

void loop() {
  delay(500);
//  digitalWrite(pinLED1, !(digitalRead(pinLED1)));
//  Serial.print(counter);
  u8x8.setCursor(0, 0);
  u8x8.print(counter);
  u8x8.print(":");
  counter++;
}
