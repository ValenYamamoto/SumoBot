#include "Motor.h"
#include "Arduino.h"

Motor::~Motor() {
  stopMotor();
}

void Motor::setPower(double power) {
  if (power == 0) {
    stopMotor();
  } else {
    int pwm = abs((int) (255 * power));
    bool direct = getDirection(power);
//    Serial.print("PWM     ");
//    Serial.print(pwm);
//    Serial.print("  ");
//    Serial.println(power);
    setDirection(direct);
    analogWrite(EN, pwm);

  }
}

void Motor::setInverse(bool invert) {
  inverse = invert;
}

bool Motor::getDirection(double power) {
  bool direct = false;

  direct = (power > 0) ? !inverse : inverse;

  return direct;
}

void Motor::setDirection(bool direct) {
  if (direct) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }
}

void Motor::stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

}
