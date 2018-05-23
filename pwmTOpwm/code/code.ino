/*
  PWM to PWM

  This example change the a pwm_in pulse in to other pwm_out pulse.
  Oled display integration: SCL = 3 -- SDA = 2

  Theory of PWM signal in Arduino:
  Arduino PWM has period of 490Hz -> 0.002040s
  This means that the PWM singal gose to 0 = 0Hz = 0s to 255 = 490Hz = 0.002040s
  pulseIn return us, so 0.002040s become 2040 us.

*/

#include <U8x8lib.h>
#define pot_pin A0
#define pwm_in_pin A1
#define pwm_out_pin 6
#define ref 500 // refresh the screen ms

// ------ Correlation
#define Vpot_max 720 // that value is correlated to the EMA_a_Vpot
// if you want to change the EMA_a_Vpot, you must change the Vpot_max.
// Yes, i want to change EMA_a_Vpot:
// 1. change 0 < EMA_a_Vpot < 1
// 2. uncomment #define calibration
//#define calibration
// 3. put the potentiometer at the maximum value
// 4. change Vpot_max to the maximum value you have read from the serial + 5
// 5. comment #define calibration

long previousMillis = 0;
int pwm_out = 0;

float EMA_a_Vpot = 0.6;      //initialization of EMA
int EMA_S_Vpot = 0;

float EMA_a_pulse = 0.4;
int EMA_S_pulse = 0;

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

void setup() {
  //Serial.begin(115200);
  u8x8.begin();
  u8x8.setFont(u8x8_font_pxplustandynewtv_u);
  EMA_S_Vpot = analogRead(pot_pin);  //set EMA S for t=1
}

void loop() {

  // Read the PWM_in
  unsigned long pulse = pulseIn(pwm_in_pin, HIGH); // pulse 0 - 2040
  // media pulse
  EMA_S_pulse = (EMA_a_pulse * pulse) + ((1 - EMA_a_pulse) * EMA_S_pulse); //run the EMA
  pwm_out = map(EMA_S_pulse, 0, 2040, 0, 255);

  // Read Vpot
  int Vpot = analogRead(pot_pin);  // Vpot 0 - 1023
  // media Vpot
  EMA_S_Vpot = (EMA_a_Vpot * Vpot) + ((1 - EMA_a_Vpot) * EMA_S_Vpot); //run the EMA
#ifdef calibration
  Serial.println(EMA_S_Vpot);
#endif
  EMA_S_Vpot = map(EMA_S_Vpot, 0, Vpot_max, 0, 255);

  if ( pulse > 2 ) { // Is the Laser ON ?
    if (EMA_S_Vpot > 5) {  // Vpot > Vpot_min_sensibility -> put PWM_out + Vpot
      pwm_out = pwm_out + ( map( EMA_S_Vpot, 0, 255, 0, 255 - pwm_out ) );
      analogWrite(pwm_out_pin, pwm_out);
    }

    else {// Vpot < Vpot_min_sensibility -> copy the PWM_in to PWM_out
      analogWrite(pwm_out_pin, pwm_out);
    }
  }
  else { // The laser is OFF.
    analogWrite(pwm_out_pin, 0);
    pwm_out = 0;
  }

  // ------------- Display
  if (millis() - previousMillis >= ref) {
    byte val = 0;
    previousMillis = millis();

    u8x8.setCursor(2, 1);
    u8x8.print("PWM IN:");
    val = map(pulse, 0, 2040, 0, 100);

    if (val < 10) {
      u8x8.setCursor(11, 1);
      u8x8.print(".");
    }
    else {
      u8x8.setCursor(10, 1);
      u8x8.print(val);
      u8x8.setCursor(13, 1);
      u8x8.print("%");
    }

    u8x8.setCursor(2, 12);
    u8x8.print("V POT :");
    val = map(EMA_S_Vpot, 0, 255, 0, 100);
    if (val < 10) {
      u8x8.setCursor(11, 12);
      u8x8.print(" ");
    }
    u8x8.setCursor(10, 12);
    u8x8.print(val);
    u8x8.setCursor(13, 12);
    u8x8.print("%");

    u8x8.setCursor(2, 23);
    u8x8.print("PWM OUT:");
    val = map(pwm_out, 0, 255, 0, 100);
    if (val < 10) {
      u8x8.setCursor(11, 23);
      u8x8.print(" ");
    }
    u8x8.setCursor(10, 23);
    u8x8.print(val);
    u8x8.setCursor(13, 23);
    u8x8.print("%");
  }
}
