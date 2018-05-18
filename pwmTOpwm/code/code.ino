/*
  PWM to PWM

  Arduino PWM has period of 490Hz -> 0.002040s
  This means that the PWM singal gose to 0 = 0Hz = 0s to 255 = 490Hz = 0.002040s
  pulseIn return us, so 0.002040s become 2040 us.

*/

#include <U8x8lib.h>
#define pot_pin A0
#define pwm_in_pin A1
#define pwm_out_pin 6
//#define Vpot_min_sensibility 2
#define ref 500 // refrash the screen ms
#define Vpot_max 720 // that value is correlated to the EMA_a_Vpot

long previousMillis = 0;
int pwm_out = 0;

float EMA_a_Vpot = 0.6;      //initialization of EMA alpha
int EMA_S_Vpot = 0;

U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

void setup() {
  Serial.begin(115200);
  u8x8.begin();
  u8x8.setFont(u8x8_font_pxplustandynewtv_u);
  EMA_S_Vpot = analogRead(pot_pin);  //set EMA S for t=1
}

void loop() {

  // Read the PWM_in
  int pulse = pulseIn(pwm_in_pin, HIGH); // pulse 0 - 2040

  // Read Vpot
  int Vpot = analogRead(pot_pin);  // Vpot 0 - 1023
  // media Vpot
  EMA_S_Vpot = (EMA_a_Vpot * Vpot) + ((1 - EMA_a_Vpot) * EMA_S_Vpot); //run the EMA
  //Serial.println(EMA_S_Vpot);
  EMA_S_Vpot = map(EMA_S_Vpot, 0, Vpot_max, 0, 255);

  if ( pulse > 1 ) { // Is the Laser ON ?
    if (EMA_S_Vpot > 0) {  // Vpot > Vpot_min_sensibility -> put PWM_out + Vpot
      pwm_out = map(pulse, 0, 2040, 0, 255);
      pwm_out = pwm_out + ( map( EMA_S_Vpot, 0, 255, 0, 255 - pwm_out ) );
      analogWrite(pwm_out_pin, pwm_out);
    }

    else {// Vpot < Vpot_min_sensibility -> copy the PWM_in to PWM_out
      pwm_out = map(pulse, 0, 2040, 0, 255);
      analogWrite(pwm_out_pin, pwm_out);
    }
  }

  //Serial.println(EMA_S_Vpot_print);

  // ------------- Display
  if (millis() - previousMillis >= ref) {
    u8x8.setCursor(2, 1);
    u8x8.print("PWM IN:");
    u8x8.setCursor(10, 1);
    u8x8.print(map(pulse, 0, 2040, 0, 100));
    u8x8.setCursor(13, 1);
    u8x8.print("%");

    u8x8.setCursor(2, 12);
    u8x8.print("V POT :");
    u8x8.setCursor(10, 12);
    u8x8.print(map(EMA_S_Vpot, 0, 255, 0, 100));
    u8x8.setCursor(13, 12);
    u8x8.print("%");

    u8x8.setCursor(2, 23);
    u8x8.print("PWM OUT:");
    u8x8.setCursor(10, 23);
    u8x8.print(map(pwm_out, 0, 255, 0, 100));
    u8x8.setCursor(13, 23);
    u8x8.print("%");

  }
}
