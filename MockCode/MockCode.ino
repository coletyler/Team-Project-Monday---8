//Code Created By Cole Tyler
//Date: November 2, 2018
//This is code for Cole Tylers 3rd year project for SYSC 3010

#include <TimeLib.h> // Library that allows us to use Time with much easier access 

boolean inDistress = false; // stores the value of true if in distress
boolean BtwTemperature = true; // stores the value of the body temperature if between the appropriate values 
boolean BtwHeartRate = true; // stores the value of the heart rate if between the appropriate values 

int Time; // Variable that stores the time in minutes (seconds in tests)
float currentTemperature; // stores the value for the current Temperature of the device
int currentHeartRate; // stores the value for the current Heart Rate of the device
double currentNavigation[2]; // stores the value for the current navigational coordinates of the device, currentNavigation[0] = x = latitude, currentNavigation[1] = y = Longitude

//Sets up the setup of the device
void setup(){
  Serial.begin(9600);   //begin the serial moniter at 9600 bouds
}

//This function set the value of the currentHeartRate
void getHeartRate() {
  currentHeartRate = 75;  
}

//This function set the value of the currentTemperature
void getTemperature() {
 currentTemperature = 99.0;
}

//This function set the value of the currentNavigation
void getNavigation() {
  currentNavigation[0] = 0;
  currentNavigation[1] = 0;
}

// This function sets BtwTemperature or BtwHeartRate to equal false if the currentTemperature or currentHeartRate are not in the correct parameters 
void CheckSensors() {
  if (currentTemperature > 100.9 || currentTemperature < 95 ) {
    BtwTemperature = false;
  } if (currentHeartRate > 100 || currentHeartRate < 50) {
    BtwHeartRate = false;
  }
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
