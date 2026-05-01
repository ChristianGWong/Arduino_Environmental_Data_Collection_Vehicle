//Written by Christian Wong
//This module includes all the essential functions for managing the SD card module
//Dual file writing method inspired by Group 3
//All print statements with string literals are written with the F() macro to save SRAM

//Import data to record
extern float temperature;
extern int brightness;
extern float lat, lon;
extern String clock;

//Initialize the SD Card; include in setup()
void initialize_SD(){
  //Check if SD card is there
  Serial.println(F("\nInitializing SD card"));
  if(SD.begin(CS_PIN)){
    Serial.println(F("Successfully initialized; card ready")); //Was able to find the card
    }
  else{
    Serial.println(F("!!ERROR!! SD card cannot be read! Please insert SD and reset Arduino to save data.")); //Could not find card
    SD_disabled = true; //Turn off card functionality until reset
  }

  //Initialize pins and attach hardware interrupt to SD button
  pinMode(CS_PIN, OUTPUT); //Chip select pin
  pinMode(SD_BUTTON, INPUT); //Button for timestamp function
  attachInterrupt(digitalPinToInterrupt(SD_BUTTON), queue_timestamp, RISING); //Button interrupt triggers timestamp queueing
}

//Cue program to timestamp next recording entry
void queue_timestamp(){
  if(SD_disabled){ //If Arduino failed initializing with an SD card, don't collect any data 
    Serial.println(F("Error accessing SD card. Please insert SD and reset Arduino."));
    return;
  }
  
  Serial.println(F("Time stamp queued")); //Announce that next entry will be marked
  timestamp_queued = true; //Let Arduino know to mark the next entry and add it to a separate file during writing
}

//Write data to SD card; include in main loop and run once per second
void write_to_SD(){
  if(timestamp_queued){ //If a timestamp is queued, add it to the log
    write_to_file(TIMESTAMPS_FILENAME);
  }
  write_to_file(MAIN_FILENAME); //Add sensor data to file
}

//Add sensor data to data log file
void write_to_file(String filename){
  //Open Data.csv
  File datafile = SD.open(filename, FILE_WRITE);
  if(!datafile){ //File could not be opened
    Serial.print(F("Couldn't write to file: "));
    Serial.println(filename); 
    return; //Stop function
  }

  //File is present on SD card
  Serial.print(F("Writing to file: ")); //Announce that file is being written to
  Serial.println(filename); 

  //Record data
  if(filename == TIMESTAMPS_FILENAME){
    datafile.print(++timestamp_number); //If saving to timestamps file, index each timestamp
    datafile.print(F(","));
  }
  datafile.print(clock); //Record current time
  datafile.print(F(","));
  datafile.print(stopwatch); //Record the time in seconds since program started
  datafile.print(F(","));
  datafile.print(temperature); //Record temperature 
  datafile.print(F(","));
  datafile.print(brightness); //Record photoresistor value
  datafile.print(F(","));
  datafile.print(lat); //Record latitude
  datafile.print(F(","));
  datafile.print(lon); //Record longitude

  if(timestamp_queued && filename == MAIN_FILENAME){ //If a timestamp is queued, mark the data entry as timestamped
    datafile.print(F(","));
    datafile.print(F("!!Timestamped!!"));
    Serial.print(F("Time stamp applied at ")); Serial.println(clock);
    timestamp_queued = false; //Clear the queue
  }

  datafile.print(F("\n")); //End of the row
  datafile.close(); //Save what was just written
}