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

const int Dash = 11;
const int Space = 10;
volatile int Voltage;                                  // Tenths of a volt
volatile int Buffer[2] = { Dash, Dash };

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
  ADCSetup();
}

void ADCSetup () {
  VREF.CTRLA = VREF_ADC0REFSEL_1V1_gc;
//  ADC0.CTRLC = ADC_REFSEL_VDDREF_gc | ADC_PRESC_DIV256_gc; // 78kHz clock
  ADC0.MUXPOS = ADC_MUXPOS_INTREF_gc;                  // Measure INTREF
  ADC0.CTRLA = ADC_ENABLE_bm;                          // Single, 10-bit
}

void MeasureVoltage () {
  ADC0.COMMAND = ADC_STCONV_bm;                        // Start conversion
  while (ADC0.COMMAND & ADC_STCONV_bm);                // Wait for completion
  uint16_t adc_reading = ADC0.RES;                     // ADC conversion result
  uint16_t voltage = 11264 / adc_reading;
  Buffer[0] = voltage / 10; Buffer[1] = voltage % 10;
}

void loop() {
  delay(500);
  //  digitalWrite(pinLED1, !(digitalRead(pinLED1)));
  //  Serial.print(counter);
  u8x8.setCursor(0, 0);
  MeasureVoltage();
  u8x8.print(Buffer[0]);
  u8x8.print(",");
  u8x8.print(Buffer[1]);
}
