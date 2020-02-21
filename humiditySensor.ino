/* So far the code is only for the sensor  completely put into the soil,
  not for layers,
  not for partially put in ...


  I use 2 buttons at 6,7 for triggering the calibration modes


  Measurments are stored in EEPROM  1024 Byte 
  For more details look at the code below

*/




// include the libraries code:
#include <LiquidCrystal.h>
#include <EEPROM.h>  // to store measurment values in the eeprom max 1024 Bytes


/*
  PIN SETUP
*/
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // initialize the library with the numbers of the interface pins
int sensorPin = A0;  // select the input pin for the potentiometer  control the visibility on the display

int a = 0;
int counter = 0;
int address = 0;


/*
  Your Calibration measurements put in here
*/

float MAX_ANALOG_SENSOR_VALUE = 574; // This is the MIN humidity
float MIN_ANALOG_SENSOR_VALUE = 230;//This is the MAX humidity  ... yes it's reciprocal ...



/*
  Global variables
*/

unsigned int sensorValue=0;
unsigned int cachedSensorValue=1;

byte sensorValueByte1 = 0;  // variable to store the value coming from the sensor
byte sensorValueByte2 = 0;  // variable to store the value coming from the sensor

byte counterByte1=0;
byte counterByte2=0;


float sensorValueInPercent = 0;
int pinCalibrateHigh = 6; // button to start the calibration for low humidity
int pinCalibrateLow = 7;  // button to start the calibration for lhigh humidity




void setup() {

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(pinCalibrateHigh, INPUT);
  pinMode(pinCalibrateLow, INPUT);
}








void loop() {

   
  


  sensorValue = analogRead(sensorPin);   // read the value from the sensor:

  sensorValueByte1=sensorValue /100;
  sensorValueByte2=sensorValue - (sensorValueByte1)*100;


//Calibration Value 2 through button 1 pressed
//ToDo: store in EEPROM

  if (digitalRead(pinCalibrateHigh)) {
    lcd.clear();
    MIN_ANALOG_SENSOR_VALUE = sensorValue;
    lcd.print("AnalogIn: ");
    lcd.print(MIN_ANALOG_SENSOR_VALUE);
    delay(3000);
  }


 //Calibration Value 2 through button 2 pressed
  if (digitalRead(pinCalibrateLow)) {
    MAX_ANALOG_SENSOR_VALUE = sensorValue;
    lcd.clear();
    lcd.print("AnalogIn: ");
    lcd.print(MAX_ANALOG_SENSOR_VALUE);
    delay(3000);
  }




/*
 *  Store the measurements in the EEPROM 
 *  A value is stored in 2 Bytes
 *  If the value has not changed a counter stores the number of unchanged measurments and this number will later be stored in the EEPROM to decrease EEPROM writes problems and saves storage
 */
 
  if (cachedSensorValue!=sensorValue) {
    if (counter == 0) {
      EEPROM.write(address , sensorValueByte1);
      EEPROM.write(address + 1 , sensorValueByte2);
       address = address + 2;
    }

    else {
      counterByte1=counter /100 ;    
        
      EEPROM.write(address, counterByte1);
      EEPROM.write(address + 1, counterByte2);
      EEPROM.write(address + 2, sensorValueByte1);
      EEPROM.write(address + 3, sensorValueByte2);
      
      address = address + 4; // because 2 Bytes are used for the new  measured value and 2 bytes are used for the previous count of the unchanged measurements   address +4 as new starting point to store a value 
      
    }

    counter = 0;
   
  }


  else {
    counter = counter + 1; // when the measurements don't differ 
  }


//Display output of the measurementvalue of the sensor 
  lcd.print("AnalogIn: ");
  lcd.print(sensorValue);
  lcd.setCursor(0, 1);
  sensorValueInPercent = 100 - (((sensorValue - MIN_ANALOG_SENSOR_VALUE) / (MAX_ANALOG_SENSOR_VALUE - MIN_ANALOG_SENSOR_VALUE)) * 100); // convert into %



cachedSensorValue=sensorValue; // for the lookup if it is necessary to store the next measured value or to count this value ...



  /*
    Serial output
  */
  //Serial.print("Feuchte in %: ");
  //Serial.println(sensorValue);


  /*
    LCD output of the calculated % of humidity
  */
  lcd.print("Humidity: ");
  lcd.print(sensorValueInPercent, 2);
  lcd.print("%");



  delay(3000); // how long you want to see one measurment while no other measurments are taken ...
  lcd.clear();





/*
 *  For testing purposes readout EEPROM
 */
 
/*
Serial.begin(9600);
Serial.println("EEPROM length");
Serial.println(EEPROM.length());
while (a < EEPROM.length()) {
    Serial.println(EEPROM.read(a));


    a = a + 1;
  }
  a=0;

Serial.println("Finito");
Serial.end();
*/





}
