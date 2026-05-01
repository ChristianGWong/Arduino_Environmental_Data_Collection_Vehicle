/***************************************************************************************************
Project 2 Combined Code by Ethan Lahip, Khai Lam, and Christian Wong
Last updated: 11/10/2025 (Version: 3.0)
  This Arduino file combines the 

***************************************************************************************************/
#include "Motors.h" //Important variables and declarations for Motors.ino
#include "LCD_SD_header.h" //Important variables and declarations for both LCD.ino and SD.ino files

unsigned long update_time = 1000; //Timer for how long until the next update cycle in ms

void setup() {
  Serial.begin(9600); //Begin Serial communication for debugging

  //Initialize all devices
  motor_setup();
  gps_setup(); 
  temp_setup(); 
  initialize_SD();
  initialize_LCD();
}

void loop() {
  sensor_temp(); //from Temperature.ino || checking temperature
  light_sensor(); //from Light.ino || checking brightness
  gps_sensor(); //from GPS.ino || checking GPS coords and time

  drive(); //From motors.ino || Control the car with the joystick

  //Every 1 second...
  if(millis() >= update_time){ //Once millis() passes update_time
    stopwatch++; //Update stopwatch
    write_to_SD(); //from SD.ino || Write to the SD card
    write_to_LCD(); //from LCD.ino || Update LCD screen
    update_time = millis() + 1000; //Update time is a second ahead of regular time again
  }

  //Check constantly if timestamp is queued and print a ! in the corner of the LCD if there is
  timestamp_LCD_indicator(); //From LCD.ino; indicator will be erased next update cycle
}