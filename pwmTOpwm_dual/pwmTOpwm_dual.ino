/*
  PWM to PWM with Encoder

  Library:
  - Encoder: https://goo.gl/g9Udvb
  - U8x8lib : https://goo.gl/vvKczz

  This example change the a pwm_in pulse in to other pwm_in pulse.
  Oled display integration: SCL = 5 -- SDA = 4

  Theory of PWM signal in Arduino:
  Arduino PWM has period of 490Hz -> 0.002040s
  This means that the PWM singal gose to 0 = 0Hz = 0s to 255 = 490Hz = 0.002040s
  pulseIn return us, so 0.002040s become 2040 us.

  DaveCalaway
*/

#include <U8x8lib.h>
#include <Encoder.h>

#define button_pin 7
#define pwm_in_pin A1
#define pwm_out_pin 6
#define ref 500 // refresh the screen ms

long previousMillis = 0;
int pwm_in = 0;
int pwm_out = 0;
bool stato = 0;
float EMA_a_pulse = 0.4;
unsigned long EMA_S_pulse = 0;
int oldPosition  = -999;
int oldpwm_in = 0;
int newPosition = 0;

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc(3, 2); // on the Pro Mini / UNO ecc....

// OLEDs without Reset of the Display
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 5, /* data=*/ 4, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  //Serial.begin(115200);
  pinMode(button_pin, INPUT_PULLUP);
  u8x8.begin();
  u8x8.setFont(u8x8_font_pxplustandynewtv_u);
}

void loop() {

  // Read the PWM_in
  unsigned long pulse = pulseIn(pwm_in_pin, HIGH, 125000); // pulse 0 - 2040
  // media pulse
  EMA_S_pulse = (EMA_a_pulse * pulse) + ((1 - EMA_a_pulse) * EMA_S_pulse); //run the EMA
  pwm_in = map(EMA_S_pulse, 0, 2040, 0, 100);
  //Serial.println(pulse);
  // LASER ON
  if ( pulse > 10 ) {
    stato = 1;
    // Reset
    if (digitalRead(button_pin) == 0) {
      delay(15);
      myEnc.write(0);
    }
    // Read Encoder
    else {
      newPosition = myEnc.read();
      // 0 < pwm_in + newPosition < 99
      if ( ((pwm_in + newPosition) <= 98) && ((pwm_in + newPosition) > 2)) {
        pwm_out = map(pwm_in + newPosition, 0, 100, 0, 255);
        analogWrite(pwm_out_pin, pwm_out);
      }
      else {
        if ( pwm_in + newPosition > 98 ) {
          newPosition = 98 - pwm_in; // calculate the max/min value can be displayed
          myEnc.write(newPosition);
        }
        else { // pwm_in + (-)newPosition < 0
          newPosition = 98 - pwm_in; // calculate the max/min value can be displayed
          newPosition = (-1) * newPosition;
          myEnc.write(newPosition);
        }
      }
    }
  }
  // LASER OFF
  else {
    stato = 0;
    analogWrite(pwm_out_pin, 0);
  }

  // ------------- Display  -------------
  if (millis() - previousMillis >= ref && pulse != 0 ) {
    previousMillis = millis();

    u8x8.setCursor(2, 1);
    u8x8.print("PWM IN:");
    if ( stato == 0)
      pwm_in = 0;
    if (pwm_in < 10) {
      u8x8.setCursor(11, 1);
      u8x8.print(".");
    }
    else {
      u8x8.setCursor(10, 1);
      u8x8.print(pwm_in);
      u8x8.setCursor(13, 1);
      u8x8.print("%");
    }

    u8x8.setCursor(2, 12);
    u8x8.print("V POT :");
    if (newPosition < 10 && newPosition > -10) {
      u8x8.setCursor(11, 12);
      u8x8.print("  ");
    }
    u8x8.setCursor(10, 12);
    u8x8.print(newPosition);
    u8x8.setCursor(13, 12);
    u8x8.print("%");

    u8x8.setCursor(2, 23);
    u8x8.print("PWM OUT:");
    int out = pwm_in + newPosition;
    if ( stato == 0)
      out = 0;
    if (out < 10) {
      u8x8.setCursor(11, 23);
      u8x8.print(" ");
    }
    u8x8.setCursor(10, 23);
    u8x8.print(out);
    u8x8.setCursor(13, 23);
    u8x8.print("%");
  }
}
