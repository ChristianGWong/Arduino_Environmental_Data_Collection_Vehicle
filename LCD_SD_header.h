//Written by Christian Wong
//This file includes and declares several essential libraries and variables for use in the LCD.ino and SD.ino files

/*Libraries*/
#include <SD.h> //SD card library
#include <LiquidCrystal_I2C.h> //LCD I2C library
#include "CustomCharacters.h" //Custom characters for LCD display

/*Pins and peripherals*/
LiquidCrystal_I2C lcd(0x3F, 16, 2); //LCD display at address 0x3F
//CSK = 13 *Hardcoded; cannot be modified*
//MISO = 12 *Hardcoded; cannot be modified*
//MOSI = 11 *Hardcoded; cannot be modified*
#define CS_PIN 10 //CS pin for SD card Module
#define SD_BUTTON 2 //Button for activating SD card time stamp
#define MAIN_FILENAME "Data.csv" //Name of the complete data file
#define TIMESTAMPS_FILENAME "Times.csv" //Name of the abridged data file with only the time stamps

/*SD card and LCD variables*/
bool SD_disabled = false;
  //true: SD card can be used at this time
  //false: SD card cannot be used at this time
volatile bool timestamp_queued = false;
  //true: Next LCD/SD update, data will be timestamped and recorded into another file in addition to the regular data file
  //false: Data will be recorded as regular
int timestamp_number = 0; //Number that counts up the timestamps
unsigned int stopwatch = 0; //Stopwatch for counting up seconds
int lcdMode = 0; //Sets what data to display on the LCD 