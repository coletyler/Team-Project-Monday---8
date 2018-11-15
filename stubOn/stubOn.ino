//Code Created By Cole Tyler
//Date: November 2, 2018
//This is code for Cole Tylers 3rd year project for SYSC 3010

#include <LiquidCrystal.h> // Library that allows us to use the LCD screen with much easier access 
#include <OneWire.h> // Library that also helps us use the Temperature with much easier access 
#include <DallasTemperature.h> // Library that allows us to use Temperature with much easier access 
#include "TinyGPS++.h" // Library that allows us to use the GPS system with much easier access 
#include "SoftwareSerial.h" // Library that also helps us use the GPS system with much easier access 
#include <TimeLib.h> // Library that allows us to use Time with much easier access 

LiquidCrystal lcd(12, 11, 5, 4, 8, 10); // sets up the pins to the LCD screen
#define led 13                //sets LED to pin 13
#define DistressButton 3      //sets DistressButton to pin 3 (INT1)
#define ResetButton 2      //sets ResetButton to pin 2 (INT0)
#define HeartRate A0      //sets HeartRate sensor to pin A0
#define Temperature A1      //sets Temperature sensor to pin A1
#define contrast 9         //sets the contrast for the LCD screen to pin 9

//This is the value for the stub that is on
boolean inDistress = true; // stores the value of true if in distress

boolean BtwTemperature = true; // stores the value of the body temperature if between the appropriate values 
boolean BtwHeartRate = true; // stores the value of the heart rate if between the appropriate values 

int Time; // Variable that stores the time in minutes (seconds in tests)
float currentTemperature; // stores the value for the current Temperature of the device
int currentHeartRate; // stores the value for the current Heart Rate of the device
double currentNavigation[2]; // stores the value for the current navigational coordinates of the device, currentNavigation[0] = x = latitude, currentNavigation[1] = y = Longitude

OneWire oneWire(Temperature); // Setup a oneWire instance to communicate with any OneWire devices  
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature. 

SoftwareSerial serial_connection(7, 6); //sets up the pins 6, 7 for the GPS system
TinyGPSPlus gps;  //This is the GPS object that will pretty much do all the grunt work with the NMEA data

// creates a heart shape symbol
byte HeartRateChar[8] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B11111,
  B01110,
  B00100};
// the function/action that is used when the reset interrup is activated   
// this resets the inDistress, BtwTemperature, and BtwHeartRate to there default values
void Reset() {
  inDistress = false;
  BtwTemperature = true;
  BtwHeartRate = true;
  delay(500);
}

//Sets up the setup of the device
void setup(){
  lcd.createChar(1, HeartRateChar); // creates the heart symbol
  lcd.begin(16, 2); // Starts up the size of LCD screen
  lcd.clear(); // clears the LCD screen just incase something is already loaded on it
  Serial.begin(9600);   //begin the serial moniter at 9600 bouds
  serial_connection.begin(9600); // Start up the Software Serial library 
  sensors.begin(); // Start up the Dallas Temperature library 
  pinMode(led, OUTPUT); //define led as an output
  pinMode(DistressButton, INPUT_PULLUP); //define DistressButton as an input, and because the serial is on it has to be a pullpu
  pinMode(ResetButton, INPUT_PULLUP); //define ResetButton as an input, and because the serial is on it has to be a pullpu
  pinMode(Temperature, INPUT); //define Temperature as an input
  pinMode(HeartRate, INPUT); //define HeartRate as an input
  pinMode(contrast, OUTPUT); //define contrast as an output
  analogWrite(contrast, 100); // '100' are the set value for the contrast
  attachInterrupt(digitalPinToInterrupt(ResetButton), Reset, CHANGE); // creates an interrup on ResetButton to pin 2 (INT0), and when the state is CHANGED at pin 2 it activates the function Reset

}

//This function displays the Alert 
void Alert() {
  lcd.clear();
  delay(100);
  if (inDistress == true) {
    lcd.print("   ALERT!!"); 
    lcd.setCursor(0,1);
    lcd.print("In Distress");
  }else if (BtwTemperature == false) {
    lcd.print("   ALERT!!");
    lcd.setCursor(0,1);
    lcd.print("Temp is low/high");
  }else if (BtwHeartRate == false) {
    lcd.print("   ALERT!!");
    lcd.setCursor(0,1);
    lcd.print("HR is low/high");
  } 
}

//This function set the value of the currentHeartRate
void getHeartRate() {
  int Rate = 0; // to store the average heart rate
  for (int i = 0; i < 100; i++) { // this will calculate the average heart rate
    Rate = Rate + analogRead(HeartRate)/ 12;
    delay(1); // this will allow it to record a new value for the average
  }
  currentHeartRate = Rate/100; // sets the currentHeartRate which is the average heart rate 
}

//This function set the value of the currentTemperature
void getTemperature() {
 sensors.requestTemperatures(); // Send the command to get temperature readings 
 currentTemperature = sensors.getTempCByIndex(0); // gets the first IC on the wire which is the Temperature, 0 refers to the first IC on the wire 
 currentTemperature = ((currentTemperature *9)/5) + 37; // sets the currentTemperature to fahrenheit (personal preference)
}

//This function set the value of the currentNavigation
void getNavigation() {
  for (int i = 0; i<20000;i++) { // the loop allows the navigation system to have enough time to collect the data 
    while(serial_connection.available()) {
      gps.encode(serial_connection.read()); //this feeds the NMEA data into the libaray one char at a time 
    }
    if (gps.location.isUpdated()) { //this will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in 
      currentNavigation[0] = gps.location.lat(); // sets the latitude of the device 
      currentNavigation[1] = gps.location.lng(); // sets the longitude of the device 
    }
  }
}

// This function sets BtwTemperature or BtwHeartRate to equal false if the currentTemperature or currentHeartRate are not in the correct parameters 
void CheckSensors() {
  if (currentTemperature > 100.9 || currentTemperature < 95 ) { // if your Body Temperature is less than 95 you are an unheathly temperature and need to get warm or if your Body Temperature is more than 100.9 you got a fever
    BtwTemperature = false;
  } if (currentHeartRate > 140 || currentHeartRate < 45) { // if your Heart rate is less than 45 or more than 140 you should see a doctor 
    BtwHeartRate = false;
  }
}

//This function displays the normal display on the LCD screen 
void Display() {
   lcd.clear();
   lcd.write(byte(1)); // this symbol repersents the Heart Rate 
   lcd.print(":");
   lcd.print(currentHeartRate);
   lcd.print(" Temp: ");
   lcd.print(currentTemperature, 1);
   lcd.setCursor(0,1);
   lcd.print("Nav:");
   lcd.print(currentNavigation[0], 2); // Latitude
   lcd.print(",");
   lcd.print(currentNavigation[1], 2); // Longitude
   delay(2000);
   
}

// displays data on serial monitor on the arduino program
// this will allow the python program to take this data and put it in the notepad database
void SerialDisplay() {
  // displays an Alert if one is activated on the serial monitor 
  if (inDistress == true) {
    Serial.print("ALERT: IN DISTRESS, ");
  }else if (BtwTemperature == false) {
    Serial.print("ALERT: TEMP IS LOW/HIGH, ");
  }else if (BtwHeartRate == false) {
    Serial.print("ALERT: HEART RATE IS LOW/HIGH, ");
  } 
  // displays the values that are collected on the serial monitor 
  Serial.write("Heart Rate: ");
  Serial.print(currentHeartRate);
  Serial.print(" BPM, Body Temperature: ");
  Serial.print(currentTemperature, 1);
  Serial.print(" F, Navigational Coordinates:");
  Serial.print(currentNavigation[0], 2); // Latitude
  Serial.print(", ");
  Serial.println(currentNavigation[1], 2);  // Longitude
}

// This function Blinks the LED on and off
void Blink() { 
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(1000); 
}

// Main, System of the device
void loop() {
    Time = minute();// sets the vari, (test with second())
    getHeartRate(); // uses this function to set the current Heart Rate
    getTemperature(); // uses this function to set the current Body Temperature
    //getNavigation(); // uses this function to set the current navigation coordinates, DISABLE UNTIL GPS IS CONNECTED TO THE DEVICE
    CheckSensors(); // uses this function to check if the Body Temperature and Heart Rate values are between the correct parameters 
    if (inDistress == true || BtwTemperature == false || BtwHeartRate == false) {
      while(inDistress || BtwTemperature == false || BtwHeartRate == false) {
        Alert(); // activates the ALert
        Blink(); // ues the Blink function
        SerialDisplay(); // displays data on serial monitor so the python program and take this data and put it in the database
      }
    }
    Display(); // diplays the values or alerts if activated
    if(((Time%10) == 0) && (Time != 0)) { //checks if there is a remainder if there isn't that means it its been 10 minutes (in test this is seconds) and will displays data on serial monitor
      SerialDisplay(); // displays data on serial monitor so the python program and take this data and put it in the database
    }
    delay(1000); // giving the device one second delay just incase
}
