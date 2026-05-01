//Pins defined for H-bridge function
#define enA 3
#define in1 6
#define in2 7
#define enB A1
#define in3 4
#define in4 5

//Variables for joystick, reading, and calibration
#define X_pin = A2;
#define Y_pin = A3;
int xValue = 0;
int yValue = 0;
int speedValue = 0;
int center = 475;
int deadZone = 90;