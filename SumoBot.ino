#include "Motor.h"

const int EN_RIGHT_BACK = 3;
const int IN_1_RIGHT_BACK = 2;
const int IN_2_RIGHT_BACK = 4;

const int EN_RIGHT_FRONT = 5;
const int IN_1_RIGHT_FRONT = 7;
const int IN_2_RIGHT_FRONT = 8;

const int EN_LEFT_BACK = 6;
const int IN_1_LEFT_BACK = 10;
const int IN_2_LEFT_BACK = 11;

const int EN_LEFT_FRONT = 9;
const int IN_1_LEFT_FRONT = 12;
const int IN_2_LEFT_FRONT = 13;

String input = "";
long right = 0;
long left = 0;

Motor rightFront(EN_RIGHT_FRONT, IN_1_RIGHT_FRONT, IN_2_RIGHT_FRONT);
Motor rightBack(EN_RIGHT_BACK, IN_1_RIGHT_BACK, IN_2_RIGHT_BACK);
Motor leftFront(EN_LEFT_FRONT, IN_1_LEFT_FRONT, IN_2_LEFT_FRONT);
Motor leftBack(EN_LEFT_BACK, IN_1_LEFT_BACK, IN_2_LEFT_BACK);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IN_1_RIGHT_FRONT, OUTPUT);
  pinMode(IN_2_RIGHT_FRONT, OUTPUT);
  
  pinMode(IN_1_RIGHT_BACK, OUTPUT);
  pinMode(IN_2_RIGHT_BACK, OUTPUT);

  pinMode(IN_1_LEFT_FRONT, OUTPUT);
  pinMode(IN_2_LEFT_FRONT, OUTPUT);
  
  pinMode(IN_1_LEFT_BACK, OUTPUT);
  pinMode(IN_2_LEFT_BACK, OUTPUT);

  rightFront.setInverse(false);
  rightBack.setInverse(true);
  leftFront.setInverse(true);
  leftBack.setInverse(true);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char INBYTE = Serial.read();
    parseSerial2(INBYTE, left, right);

    Serial.print("HERE     ");
    Serial.print(right);
    Serial.print("  ");
    Serial.println(left);

    double rightPower = ((double) right) / 100.0;
    double leftPower = ((double) left) / 100.0;

    Serial.print(rightPower);
    Serial.print("  ");
    Serial.println(leftPower);
    arcadeDrive(rightPower, leftPower);
//    rightFront.setPower(right);
  } else {
//    for(double i = -1; i <= 1; i = i + 0.1) {
//      leftFront.setPower(i);
//      Serial.print("LEFT FRONT  ");
//      Serial.println(i);
//      delay(1000);
//    }
//    arcadeDrive(0, 0);
//    for(double i = -1; i <= 1; i = i + 0.1) {
//      leftBack.setPower(i);
//      Serial.print("LEFT BACK  ");
//      Serial.println(i);
//      delay(1000);
//    }
//    for(double i = -1; i <= 1; i = i + 0.1) {
//      rightFront.setPower(i);
//      Serial.print("RIGHT FRONT  ");
//      Serial.println(i);
//      delay(1000);
//    }
//    for(double i = -1; i <= 1; i = i + 0.1) {
//      rightBack.setPower(i);
//      Serial.print("RIGHT BACK  ");
//      Serial.println(i);
//      delay(1000);
//    }
//    rightFront.setPower(1);
//    rightBack.setPower(1);
//    leftFront.setPower(1);
//    leftBack.setPower(1);
  }
}

String parseSerial(char in){
  if(in != '<'){
    input += in;
    return "";
  }
  String finalString = input;
  input = "";
  return finalString;
}

void parseSerial2(char in, long &left, long &right) {
  if(in != '<' && in != '>') {
    input += in;
  }
  if(in == '<') {
//    Serial.println("Left");
    left = input.toInt();
//    Serial.println(left);
    input = "";
  }
  if(in == '>') {
//    Serial.println("Right");
    right = input.toInt();
//    Serial.println(right);
    input = "";
  }
}

void arcadeDrive(double right, double left) {
  rightFront.setPower(right);
  rightBack.setPower(right);
  leftFront.setPower(left);
  leftBack.setPower(left);
}
