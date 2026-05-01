//Written by Christian Wong
//This module includes all the essential functions for managing the LCD display
//All print statements with string literals are written with the F() macro to save SRAM

//Import data to record
extern float temperature;
extern int brightness;
extern float lat, lon;
extern String clock;

//Initialize LCD; include in setup()
void initialize_LCD() {
  //Prepare LCD for displaying text
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");  //Let user know program reset

  //Custom character initialization
  lcd.createChar(0, download_0);
  lcd.createChar(1, download_1);
  lcd.createChar(2, SD_fail_0);
  lcd.createChar(3, SD_fail_1);

  delay(1000);
  lcd.clear();
}

//Write the data to LCD screen; include in main loop and only trigger every second
void write_to_LCD() {
  //Prints the stopwatch timer in the first line; updates every 1 second
  lcd.print("Time: ");
  lcd.setCursor(6, 0);
  lcd.print("          ");
  lcd.setCursor(6, 0);
  lcd.print(stopwatch);
  lcd.setCursor(0, 1);

  //Every five seconds on the stopwatch, change the sensor data to be printed on the bottom row
  if(stopwatch%5==0){
    lcdMode++; //Go to the next mode
    if(lcdMode>3){lcdMode=0;} //Loop back to the start if the mode goes over the limit
  }

  /*Updates the bottom line of display to show one of the measurements depending on the current lcdMode value*/
  switch (lcdMode) {
    case 0:  //Temperature
      lcd.print(F("Temp: "));      //Print the name of the measured item being displayed
      lcd.print(F("          "));  //Clear any text that comes after it with white space
      lcd.setCursor(6, 1);         //Reset the cursor back to being in front of it
      lcd.print(temperature);      //Print the value
      lcd.print(F("C"));           //Print any auxiliary components like unit
      break;
    case 1:  //Photoresistor
      lcd.print("Photo: ");
      lcd.print("          ");
      lcd.setCursor(7, 1);
      lcd.print(brightness);
      break;
    case 2:  //Latitude
      lcd.print("Lati: ");
      lcd.print("          ");
      lcd.setCursor(6, 1);
      lcd.print(lat, 1);
      break;
    case 3:  //Longitude
      lcd.print("Long: ");
      lcd.print("          ");
      lcd.setCursor(6, 1);
      lcd.print(lon, 1);
      break;
  }

  //Show SD card is disabled with icon animation at top right *Idea from Khai Lam
  if (SD_disabled) {
    if (stopwatch % 2 == 0) {  //Switch character shown every 1 second
      lcd.setCursor(15, 0);        //Displayed in top right corner of LCD
      lcd.print(" ");
      lcd.setCursor(15, 0);
      lcd.write(2);
    } else {
      lcd.setCursor(15, 0);
      lcd.print(" ");
      lcd.setCursor(15, 0);
      lcd.write(3);
    }
  } 
  else { //Show SD card is being written to with icon animation at top right *Idea from Khai Lam
    if (stopwatch % 2 == 0) {
      lcd.setCursor(15, 0);
      lcd.write(0);
    } else {
      lcd.setCursor(15, 0);
      lcd.write(1);
    }
  }

  //Erase timestamp marker when timestamp queue is false
  if (!timestamp_queued) {
    lcd.setCursor(14, 0);
    lcd.print(" ");
  }
}

//Indicate on the LCD when a timestamp is queued; update constantly
void timestamp_LCD_indicator(){
  if (timestamp_queued) {
    lcd.setCursor(14, 0);
    lcd.print("!");
  }
}