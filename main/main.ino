// Test U8X8 OLED
// MegaTinyCore 2.3.2
//   Chip: ATtiny1624
//   Clock: 10MHz
//   millis()/micros() TCB1
//   Voltage for UART: Closer to 3V
//   Startup Time: 8mS

#include <U8x8lib.h> // https://github.com/olikraus/u8g2
#include <ezButton.h>

U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

//int but1 = PIN_PC0;
//int but2 = PIN_PC3;

ezButton button1(PIN_PC0);
ezButton button2(PIN_PC3);
ezButton buttonReset(PIN_PA6);

// hh:mm:ss
// h2h1:m2m1:s2s1

int h1 = 0;
int h2 = 0;
int m1 = 0;
int m2 = 0;
int s1 = 0;
int s2 = 0;

int x = 0;

unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 1000;  //the value is a number of milliseconds

void setup() {
  pinConfigure(PIN_PC0, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PC3, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PA6, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  delay(100);
  u8x8.begin();
  u8x8.setFlipMode(0);
  u8x8.setFont(u8x8_font_courB24_3x4_n);

  button1.setDebounceTime(50); // set debounce time to 50 milliseconds
  button2.setDebounceTime(50);
  buttonReset.setDebounceTime(50);

  startMillis = millis();  //initial start time
}

void loop() {
  button1.loop(); // MUST call the loop() function first
  button2.loop();
  buttonReset.loop();

  if (button1.isReleased()) {
    x = 2;
    number();
  }
  if (button2.isReleased()) {
    x = 2;
    start_timer();
  }
  if (buttonReset.isReleased()) {
    x = 0;
    h2 = 0;
    h1 = 0;
    m2 = 0;
    m1 = 0;
    s2 = 0;
    s1 = 0;
    u8x8.clearDisplay();
    print_oled();
  }
}

void print_oled() {
  u8x8.setCursor(0, 0);
  u8x8.setFont(u8x8_font_courB24_3x4_n);
  if (h2 > 0 || h1 > 0) {
    u8x8.setCursor(0, 1);
    //    u8x8.setFont(u8x8_font_7x14B_1x2_n);
    u8x8.setFont(u8x8_font_courB18_2x3_n);
    u8x8.clearDisplay();
    u8x8.print(h2);
    u8x8.print(h1);
    u8x8.print(":");
  }
  u8x8.print(m2);
  u8x8.print(m1);
  u8x8.print(":");
  u8x8.print(s2);
  u8x8.print(s1);
}

void number() {
  h2 = h1;
  h1 = m2;
  m2 = m1;
  m1 = s2;
  s2 = s1;
  s1 = x;
  print_oled();
}

void counter() {
  if (s1 > 0) {
    s1 = s1 - 1;
    return;
  }
  if (s1 == 0) {
    if (s2 > 0) {
      s1 = 9;
      s2 = s2 - 1;
      return;
    }
    if (s2 == 0) {
      if (m1 > 0) {
        s2 = 5;
        m1 = m1 - 1;
        return;
      }
      if (m1 == 0) {
        if (m2 > 0) {
          m1 = 9;
          m2 = m2 - 1;
          return;
        }
        if (m2 == 0) {
          if (h1 > 0) {
            m2 = 6;
            h1 = h1 - 1;
            return;
          }
          if (h1 == 0) {
            if (h2 > 0) {
              h1 = 9;
              h2 = h2 - 1;
              return;
            }
          }
        }
      }
    }
  }
}

void start_timer() {
  while (h2 > 0 || h1 > 0 || m2 > 0 || m1 > 0 || s2 > 0 || s1 > 0) {
    buttonReset.loop();
    if (buttonReset.isReleased()) {
      x = 0;
      h2 = 0;
      h1 = 0;
      m2 = 0;
      m1 = 0;
      s2 = 0;
      s1 = 0;
      u8x8.clearDisplay();
      print_oled();
    }
    currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
    if (currentMillis - startMillis >= period)  //test whether the period has elapsed
    {
      counter();
      startMillis = currentMillis;  //IMPORTANT to save the start time of the current LED state.
      print_oled();
    }
  }
}
