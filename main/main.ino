#include <U8x8lib.h> // https://github.com/olikraus/u8g2
#include <ezButton.h>

// setup the OLED
U8X8_SSD1306_128X32_UNIVISION_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

// Setup all Buttons
ezButton button1(PIN_PC0);
ezButton button2(PIN_PA5);
ezButton button3(PIN_PB4);
ezButton button4(PIN_PC1);
ezButton button5(PIN_PA3);
ezButton button6(PIN_PB5);
ezButton button7(PIN_PC2);
ezButton button8(PIN_PA2);
ezButton button9(PIN_PA7);
ezButton button0(PIN_PA1);
ezButton buttonStart(PIN_PC3);
ezButton buttonReset(PIN_PA6);

// int
int h1 = 0;
int h2 = 0;
int m1 = 0;
int m2 = 0;
int s1 = 0;
int s2 = 0;

int x = 0;
int hms = 0;
int ms = 0;
int s = 0;
int h = 0;
int m = 0;

// unsigned long 
unsigned long startMillis;
unsigned long currentMillis;

// Set Intervall
const unsigned long period = 1000;

// bool
bool countown_done = false;
bool reset_yes = false;

void setup() {
  // Pin configuration SetUp
  pinConfigure(PIN_PA1, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PA2, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PA3, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PA5, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PA6, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PA7, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PB4, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PB5, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PC0, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PC1, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PC2, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PC3, (PIN_DIR_INPUT | PIN_PULLUP_ON));
  pinConfigure(PIN_PA4, (PIN_DIR_OUTPUT));
  
  delay(100);
  
  // SetUp the Display
  u8x8.begin();
  u8x8.setFlipMode(0);
  u8x8.setFont(u8x8_font_courB24_3x4_n);

  // Set debounce time to 50 milliseconds for all buttons
  button1.setDebounceTime(50); 
  button2.setDebounceTime(50);
  button3.setDebounceTime(50);
  button4.setDebounceTime(50);
  button5.setDebounceTime(50);
  button6.setDebounceTime(50);
  button7.setDebounceTime(50);
  button8.setDebounceTime(50);
  button9.setDebounceTime(50);
  button0.setDebounceTime(50);
  buttonStart.setDebounceTime(50);
  buttonReset.setDebounceTime(50);

  // initial start time
  startMillis = millis();  
}

void loop() {

  // MUST call the loop() function first
  button1.loop(); 
  button2.loop();
  button3.loop();
  button4.loop();
  button5.loop();
  button6.loop();
  button7.loop();
  button8.loop();
  button9.loop();
  button0.loop();
  buttonStart.loop();
  buttonReset.loop();

  // See what button was pressed
  if (button1.isReleased()) {
    x = 1;
    number();
  }
  if (button2.isReleased()) {
    x = 2;
    number();
  }
  if (button3.isReleased()) {
    x = 3;
    number();
  }
  if (button4.isReleased()) {
    x = 4;
    number();
  }
  if (button5.isReleased()) {
    x = 5;
    number();
  }
  if (button6.isReleased()) {
    x = 6;
    number();
  }
  if (button7.isReleased()) {
    x = 7;
    number();
  }
  if (button8.isReleased()) {
    x = 8;
    number();
  }if (button9.isReleased()) {
    x = 9;
    number();
  }if (button0.isReleased()) {
    x = 0;
    number();
  }
  if (buttonStart.isReleased()) {
    reset_yes = false;
    if (hms > 0) {
      start_timer();
    }
    if (hms == 0) {
      countup();
    }
  }
  if (buttonReset.isReleased()) {
    reset_button();
  }
}

void print_oled() {
  u8x8.setCursor(0, 0);
  u8x8.setFont(u8x8_font_courB24_3x4_n);
  if (countown_done == true){
    u8x8.setCursor(1, 1);
    u8x8.setFont(u8x8_font_courB18_2x3_n);
    u8x8.print("-");
  }
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
  hms = (h2 * 10 + h1) * 3600 + (m2 * 10 + m1) * 60 + s2 * 10 + s1;
  print_oled();
}

void counter(int k) {
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    startMillis = currentMillis;  //IMPORTANT to save the start time
    hms = (h2 * 10 + h1) * 3600 + (m2 * 10 + m1) * 60 + s2 * 10 + s1;
    hms = hms + k;
    h = hms / 3600;
    h2 = h / 10;
    h1 = h % 10;
    ms = hms % 3600;
    m = ms / 60;
    m2 = m / 10;
    m1 = m % 10;
    s = ms % 60;
    s2 = s / 10;
    s1 = s % 10;
    print_oled();
  }
}

void start_timer() {
  while (reset_yes == false ) {
    buttonReset.loop();
    if (buttonReset.isReleased()) {
      reset_button();
    }
    counter(-1);
    if (hms == 0){
      countown_done = true;
      u8x8.clearDisplay();
      digitalWrite(PIN_PA4, HIGH);
      delay(500);
      digitalWrite(PIN_PA4, LOW);
      countup();
    }
  }
}

void countup() {
  while (reset_yes == false ) {
    buttonReset.loop();
    if (buttonReset.isReleased()) {
      reset_button();
    }
    counter(+1);
  }
}

void reset_button() {
  x = 0;
  hms = 0;
  h2 = 0;
  h1 = 0;
  m2 = 0;
  m1 = 0;
  s2 = 0;
  s1 = 0;
  countown_done = false;
  reset_yes = true;
  u8x8.clearDisplay();
  print_oled();
}
