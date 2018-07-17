/*
 * Sketch for the Arduino called Laser.
 * This program simulate a PWM signal from the laser controller.
 * 
 * Dave Calaway
 */

const int pwmOut = 9;

void setup() {
  //
}

void loop() {
  for (byte i = 0; i <= 255; i++) {
    analogWrite(pwmOut, i);
    delay(500);
  }

  for (byte i = 255; i <= 0; i--) {
    analogWrite(pwmOut, i);
    delay(500);
  }
}
