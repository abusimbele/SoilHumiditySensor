/* So far the code is only for the sensor  completely put into the soil,
not for layers,
not for partially put in ...


Look what you use for your calibration...


*/




// include the library code:
#include <LiquidCrystal.h>


/*
PIN SETUP
*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // initialize the library with the numbers of the interface pins
int sensorPin = A0;  // select the input pin for the potentiometer  control the visibility on the display



/*
Your Calibration measurements put in here
*/

const float MAX_ANALOG_SENSOR_VALUE = 574; // This is the MIN humidity
const float MIN_ANALOG_SENSOR_VALUE = 230;//This is the MAX humidity  ... yes it's reciprocal ... 



/*
Global variables
*/
float sensorValue = 0;  // variable to store the value coming from the sensor





void setup() {
  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  
  //pinMode(ledPin, OUTPUT);  
  Serial.begin(9600);
  
}








void loop() {
 
 
  sensorValue = analogRead(sensorPin);   // read the value from the sensor:   
  sensorValue = 100-(((sensorValue - MIN_ANALOG_SENSOR_VALUE)/(MAX_ANALOG_SENSOR_VALUE - MIN_ANALOG_SENSOR_VALUE))*100);  // convert into %
  
  
  
  /*
  Serial output
  */
  Serial.print("Feuchte in %: ");
  Serial.println(sensorValue);
  
  
    /*
  LCD output
  */
  lcd.print(sensorValue,2);  

  
  
  delay(500); // how long you want to see one measurment while no other measurments are taken ...
  lcd.clear(); 

}
