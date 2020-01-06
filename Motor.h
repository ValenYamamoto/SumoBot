#ifndef Motor_h
#define Motor_h

#include "Arduino.h"


class Motor {
  const int EN;
  const int IN1;
  const int IN2;

  bool inverse;

  public:
    Motor(int en, int in1, int in2) : EN(en), IN1(in1), IN2(in2) {
      inverse = false;
    }

    ~Motor();
    
    void setPower(double power);

    void setInverse(bool inverse);

    
  private:
    bool getDirection(double power);

    void setDirection(bool direct);

    void stopMotor();
};
#endif
