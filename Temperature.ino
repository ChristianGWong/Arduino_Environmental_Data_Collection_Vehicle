/*Variables/Functions for TMP Sensor*/
#include <Wire.h>
/***********************************************************/
const int TEMP_ADDRESS = 72;  //CHANGE THIS
/***********************************************************/
int temp;
float temperature;        //create global, used to write data
//create global, used to write data


/*Setup Function*/
void temp_setup() {
  Wire.begin();
}


/*Loop Function*/
void sensor_temp(){
  Wire.beginTransmission(TEMP_ADDRESS);
  Wire.write(0);                      //Ask TC74 to start collecting data
  Wire.endTransmission();             //Stop asking
  Wire.requestFrom(TEMP_ADDRESS, 1);  //Ask TC74 to send collected data
  while (Wire.available() == 0);       //Wait for TC74 to respond
  temperature = Wire.read();                //Store data in temperature variable
}