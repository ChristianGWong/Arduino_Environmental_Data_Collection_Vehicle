/*Variables/Functions for GPS Sensor*/
#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
float lat, lon;  // create variable for latitude and longitude object
char checkchar;
int bytesavailable;
String clock = ""; //variable for storing current time as string

/***********************************************************/
SoftwareSerial gpsSerial(8, 9);  // CHANGE THIS
/***********************************************************/
TinyGPSPlus gps;  // create gps object


/*Setup Function*/
void gps_setup() {
  gpsSerial.begin(9600);  // connect gps sensor
}


/*Loop Function*/
void gps_sensor() {
bytesavailable = gpsSerial.available();
  while (bytesavailable) {
    checkchar = gps.encode(gpsSerial.read());  // check for gps data
    if (checkchar)                             // decode gps data
    {
      lat = gps.location.lat(); // get latitude and longitude
      lon = gps.location.lng();
      
      //Serial.print("Position --> ");
      //Serial.print("lat: ");Serial.print(lat, 6);
      //Serial.print(" lon: ");Serial.println(lon, 6); // print longitude

    }
    bytesavailable = gpsSerial.available();
  }
  
  //Get the time and put it into a string
  clock = "";
  clock += ((gps.time.hour()+16)%24); //Adjust for timezone PST = UTC-8
  clock += ":";
  clock += gps.time.minute();
  clock += ":";
  clock += gps.time.second();
  //Serial.println(clock);
}