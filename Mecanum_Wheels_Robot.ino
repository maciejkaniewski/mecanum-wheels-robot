#include "Arduino.h"
#include "Wire.h"
#include "NewPing.h"
#include "DFRobot_MotorStepper.h"

#define MAX_DIST 20

// Pin Definitions
#define HCSR04B_PIN_TRIG  3
#define HCSR04B_PIN_ECHO 2
#define HCSR04F_PIN_TRIG  5
#define HCSR04F_PIN_ECHO 4
#define HCSR04L_PIN_TRIG  7
#define HCSR04L_PIN_ECHO 6
#define HCSR04R_PIN_TRIG  9
#define HCSR04R_PIN_ECHO 8

// Distance Sensors Defenitions
NewPing hcsr04B(HCSR04B_PIN_TRIG, HCSR04B_PIN_ECHO);
NewPing hcsr04F(HCSR04F_PIN_TRIG, HCSR04F_PIN_ECHO);
NewPing hcsr04L(HCSR04L_PIN_TRIG, HCSR04L_PIN_ECHO);
NewPing hcsr04R(HCSR04R_PIN_TRIG, HCSR04R_PIN_ECHO);

// Motors Definitions
DFRobot_Motor motor1(M1, A0);
DFRobot_Motor motor2(M2, A0);
DFRobot_Motor motor3(M3, A0);
DFRobot_Motor motor4(M4, A0);

// Communication Buffer
char cmd[100];
byte cmdIndex;

// Backward Distance Sensor
int hcsr04BDist = 0;
int B_flag = 0;

// Forward Distance Sensor
int hcsr04FDist = 0;
int F_flag = 0;

// Left Distance Sensor
int hcsr04LDist = 0;
int L_flag = 0;

// Right Distance Sensor
int hcsr04RDist = 0;
int R_flag = 0;

/**
   Controls motors
*/
void control_motors()
{
  if (cmd[0] == 'm') // If recieved command starts with 'm'
  {
    switch (cmd[1])
    {
      case '1': // NW Direction

        motor2.start(CCW);
        motor3.start(CW);
        break;

      case '2': // N Direction (Forward)

        F_flag = 1;
        hcsr04FDist = hcsr04F.ping_cm(30);

        if (hcsr04FDist > MAX_DIST || hcsr04FDist == 0)
        {
          motor1.start(CCW);
          motor2.start(CCW);
          motor3.start(CW);
          motor4.start(CW);
        }
        break;

      case '3': // NE Direction

        motor1.start(CCW);
        motor4.start(CW);
        break;

      case '4': // E Direction (Right)

        R_flag = 1;
        hcsr04RDist = hcsr04R.ping_cm(30);

        if (hcsr04RDist > MAX_DIST || hcsr04RDist == 0)
        {

          motor1.start(CCW);
          motor2.start(CW);
          motor3.start(CCW);
          motor4.start(CW);
        }
        break;

      case '5': // W Direction (Left)

        L_flag = 1;
        hcsr04LDist = hcsr04L.ping_cm(30);

        if (hcsr04LDist > MAX_DIST || hcsr04LDist == 0)
        {
          motor1.start(CW);
          motor2.start(CCW);
          motor3.start(CW);
          motor4.start(CCW);
        }
        break;

      case '6': // SW Direction

        motor1.start(CW);
        motor4.start(CCW);
        break;

      case '7': // S Direction (Backward)

        B_flag = 1;
        hcsr04BDist = hcsr04B.ping_cm(30);

        if (hcsr04BDist > MAX_DIST || hcsr04BDist == 0)
        {
          motor1.start(CW);
          motor2.start(CW);
          motor3.start(CCW);
          motor4.start(CCW);
        }

        break;

      case '8': // SE Direction

        motor2.start(CW);
        motor3.start(CCW);
        break;

      case '9': // Turn Around Left

        motor1.start(CW);
        motor2.start(CW);
        motor3.start(CW);
        motor4.start(CW);
        break;

      case 'A': // Turn Around Right

        motor1.start(CCW);
        motor2.start(CCW);
        motor3.start(CCW);
        motor4.start(CCW);
        break;

      default: // Stop

        B_flag = 0;
        F_flag = 0;
        L_flag = 0;
        R_flag = 0;
        motor1.stop();
        motor2.stop();
        motor3.stop();
        motor4.stop();
        break;
    }
  }
  else if (cmd[0] == 's') // If recieved command starts with 's'
  {
    // Set motors speed
    unsigned int val = atof(cmd + 1);
    motor1.speed(val);
    motor2.speed(val);
    motor3.speed(val);
    motor4.speed(val);
  }
}

void setup() {

  Serial.begin(9600);
  Serial.println("Serial initialized");
  Wire.begin();

  //Initialize D.C motor drive chip
  motor1.init();
  motor2.init();
  motor3.init();
  motor4.init();

  //Setting initial velocity (Min:0  Max:4096)
  motor1.speed(4096);
  motor2.speed(4096);
  motor3.speed(4096);
  motor4.speed(4096);
}

void loop()
{


  if (B_flag == 1)
  {
    hcsr04BDist = hcsr04B.ping_cm(30);

    if (hcsr04BDist < MAX_DIST && hcsr04BDist > 0) {
      motor1.stop();
      motor2.stop();
      motor3.stop();
      motor4.stop();
    }
  }

  if (F_flag == 1)
  {
    hcsr04FDist = hcsr04F.ping_cm(30);

    if (hcsr04FDist < MAX_DIST && hcsr04FDist > 0) {
      motor1.stop();
      motor2.stop();
      motor3.stop();
      motor4.stop();
    }
  }

  if (L_flag == 1)
  {
    hcsr04LDist = hcsr04L.ping_cm(30);

    if (hcsr04LDist < MAX_DIST && hcsr04LDist > 0) {
      motor1.stop();
      motor2.stop();
      motor3.stop();
      motor4.stop();
    }
  }

  if (R_flag == 1)
  {
    hcsr04RDist = hcsr04R.ping_cm(30);

    if (hcsr04RDist < MAX_DIST && hcsr04RDist > 0) {
      motor1.stop();
      motor2.stop();
      motor3.stop();
      motor4.stop();
    }
  }

  // Receiving commands from Bluetooth
  if (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n') {
      cmd[cmdIndex] = 0;
      control_motors();
      cmdIndex = 0;
    } else {
      cmd[cmdIndex] = c;
      if (cmdIndex < 99) cmdIndex++;
    }
  }
}
