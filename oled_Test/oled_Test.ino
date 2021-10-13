// Test u8g2 OLED
// MegaTinyCore 2.3.2
//   Chip: ATtiny1624
//   Clock: 10MHz
//   millis()/micros() TCB1
//   Voltage for UART: Closer to 3V
//   Startup Time: 8mS

#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h> // https://github.com/olikraus/u8g2 v2.28.10

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0,/* reset=*/ U8X8_PIN_NONE); 

//int pinLED1 = PIN_PC0;
int counter = 0;

void setup() {
//  delay(500);
//  pinMode(pinLED1, OUTPUT);
//  digitalWrite(pinLED1,LOW);
//  Serial.begin(115200);
//  Serial.print("Test");
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_helvR18_tr);
//  digitalWrite(pinLED1,HIGH);    
}

void loop() {
  delay(500);
//  digitalWrite(pinLED1, !(digitalRead(pinLED1)));
//  Serial.print(counter);
  u8g2.setCursor(0, 30);
  u8g2.print(counter);
  u8g2.sendBuffer();  
  counter++;
}
