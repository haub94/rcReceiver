//DEFINITIONS
#include <Arduino.h>
#include <RF24.h>
#include <Servo.h>

//servos connections
#define PR_SERVO_PIN 9    //propeller connected to pin 9
#define AL_SERVO_PIN 6    //aileron connected to pin 6
#define AR_SERVO_PIN 5    //ailoron connected to pin 5
#define EL_SERVO_PIN 10   //elevator connected to pin 10
#define RD_SERVO_PIN 3    //rudder connected to pin 3

Servo pr_servo;
Servo al_servo;
Servo ar_servo; 
Servo rd_servo;
Servo el_servo;
RF24 radio(7, 8);         //CE, CSN

const byte ADDRESS[6] = "00001"; //channel (must be the same like from the transmitter)

struct receivedData{   //max 32 bytes - its the NRF24L01 limit
  short propeller;     //joystick-value PR from the trasnmitter
  short rudder;        //joystick-value RD from the trasnmitter
  short elevator;      //joystick-value EL from the trasnmitter
  short aileron;       //joystick-value AL from the trasnmitter
};
receivedData data;           

//default init-values from the joystick (CHECK THE VALUES FROM YOUR JOYSTICK!)
//ToDo: read this values during boot from transmitter
const short PR_MAX = 695;
const short PR_MIN = -40;
const short EL_MIN = -352;
const short EL_MAX = 325;
const short RD_MIN = -327;
const short RD_MAX = 379;
const short AL_MIN = -333;
const short AL_MAX = 358;


//SETUP
void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, ADDRESS);    //set channel
  radio.setPALevel(RF24_PA_MAX);        //set power from NRF24-L01
  radio.startListening();               //define NRF24-L01 as receiver

  //servo-pin mapping
  pr_servo.attach(PR_SERVO_PIN, 1000, 2000);
  al_servo.attach(AR_SERVO_PIN);       
  ar_servo.attach(AL_SERVO_PIN);       
  el_servo.attach(AL_SERVO_PIN);       
  rd_servo.attach(RD_SERVO_PIN);       

  delay(1000);
}

//MAIN
void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(receivedData));
  }

  //Motor
  const short PR_SPEED = map(data.propeller, PR_MIN, PR_MAX, 0, 150);
  if(data.propeller >= 0){
    pr_servo.write(PR_SPEED);
  } else
    pr_servo.write(0);

  //AL
  const byte AL_SERVO_ANGLE = map(data.aileron, RD_MIN, RD_MAX, 30, 150);
  al_servo.write(AL_SERVO_ANGLE);

  //AR
  //min and max-values switched, so the AL and AR works in opposite directions (=aircraft rolls)
  const byte AR_SERVO_ANGLE = map(data.aileron, RD_MAX, RD_MIN, 30, 150); 
  ar_servo.write(AR_SERVO_ANGLE);

  //EL
  const byte EL_SERVO_ANGLE = map(data.elevator, EL_MIN, EL_MAX, 30, 150);
  el_servo.write(EL_SERVO_ANGLE);

  //RD
  const byte RD_SERVO_ANGLE = map(data.rudder, RD_MIN, RD_MAX, 30, 150);
  rd_servo.write(RD_SERVO_ANGLE);

  delay(100);
}