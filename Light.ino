/*Variables/Functions for LIGHT Sensor*/
/***********************************************************/
const int LIGHT = A0;
/***********************************************************/
int brightness;


/*Loop Function*/
void light_sensor() {
  brightness = analogRead(LIGHT);                               //Read the light sensor
}