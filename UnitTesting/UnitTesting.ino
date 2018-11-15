//Code Created By Cole Tyler
//Date: November 2, 2018
//This is code for Cole Tylers 3rd year project for SYSC 3010

boolean BtwTemperature = true; // stores the value of the body temperature if between the appropriate values 
boolean BtwHeartRate = true; // stores the value of the heart rate if between the appropriate values 

float currentTemperature; // stores the value for the current Temperature of the device
int currentHeartRate; // stores the value for the current Heart Rate of the device

//Sets up the setup of the device
void setup(){
  Serial.begin(9600);   //begin the serial moniter at 9600 bouds
}

//This function set the value of the currentHeartRate
void getHeartRate(int heart) {
  int Rate = 0; // to store the average heart rate
  for (int i = 0; i < 100; i++) { // this will calculate the average heart rate
    Rate = Rate + heart/ 12;
    delay(1); // this will allow it to record a new value for the average
  }
  currentHeartRate = Rate/100; // sets the currentHeartRate which is the average heart rate 
}

//This function set the value of the currentTemperature
void getTemperature(float temp) {
 currentTemperature = temp; // gets the first IC on the wire which is the Temperature, 0 refers to the first IC on the wire 
 currentTemperature = ((currentTemperature *9)/5) + 37; // sets the currentTemperature to fahrenheit (personal preference)
}

// This function sets BtwTemperature or BtwHeartRate to equal false if the currentTemperature or currentHeartRate are not in the correct parameters 
void CheckSensors() {
  if (currentTemperature > 100.9 || currentTemperature < 95 ) { // if your Body Temperature is less than 95 you are an unheathly temperature and need to get warm or if your Body Temperature is more than 100.9 you got a fever
    BtwTemperature = false;
  } if (currentHeartRate > 140 || currentHeartRate < 45) { // if your Heart rate is less than 45 or more than 140 you should see a doctor 
    BtwHeartRate = false;
  }
}

// Main, For Testing the system of the device
void loop() {
  float BadTemp = random(36, 38);
  float GoodTemp = random(34,36);
  int BadHR = random(1680,1920);
  int GoodHR = random(612,1260);

  BtwTemperature = true; // initialize the Body Temperature and Heart Rate to have good values so checkSensors doesnt my the values false while doing other tests 
  BtwHeartRate = true;

  getTemperature(GoodTemp); // initialize the Body Temperature and Heart Rate to have good values so checkSensors doesnt my the values false while doing other tests
  getHeartRate(GoodHR);
  
  Serial.println("Starting Testing:");
  Serial.println("Testing for Heathly Heart Rate:");
  delay(1000);
  getHeartRate(GoodHR); // uses this function to set the current Heart Rate
  CheckSensors(); // uses this function to check if the Body Temperature and Heart Rate values are between the correct parameters
  Serial.print("currentHeartRate = ");
  Serial.print(currentHeartRate);
  Serial.print(", BtwHeartRate =");
  Serial.println(BtwHeartRate);
  if (BtwHeartRate == false) {
    Serial.println("Error: Test Failed");
  } else  {
    Serial.println("Test Completed Task Successfully");
  }
  delay(1000);

  
  Serial.println("Testing for Unheathly Heart Rate:");
  delay(1000);
  getHeartRate(BadHR); // uses this function to set the current Heart Rate
  CheckSensors(); // uses this function to check if the Body Temperature and Heart Rate values are between the correct parameters
  Serial.print("currentHeartRate = ");
  Serial.print(currentHeartRate);
  Serial.print(", BtwHeartRate =");
  Serial.println(BtwHeartRate);
  if (BtwHeartRate == true) {
    Serial.println("Error: Test Failed");
  } else  {
    Serial.println("Test Completed Task Successfully");
  } 
  BtwHeartRate = true;
  delay(1000);

  
  Serial.println("Testing for Heathly Body Temperature:");
  delay(1000);
  getTemperature(GoodTemp); // uses this function to set the current Body Temperature
  CheckSensors(); // uses this function to check if the Body Temperature and Heart Rate values are between the correct parameters 
  Serial.print("currentTemperature = ");
  Serial.print(currentTemperature);
  Serial.print(", BtwTemperature =");
  Serial.println(BtwTemperature);
  if (BtwTemperature == false) {
    Serial.println("Error: Test Failed");
  } else  {
    Serial.println("Test Completed Task Successfully");
  }
  delay(1000);

  
  Serial.println("Testing for Unheathly Body Temperature:");
  delay(1000);
  getTemperature(BadTemp); // uses this function to set the current Body Temperature
  CheckSensors(); // uses this function to check if the Body Temperature and Heart Rate values are between the correct parameters 
  Serial.print("currentTemperature = ");
  Serial.print(currentTemperature);
  Serial.print(", BtwTemperature =");
  Serial.println(BtwTemperature);
  if (BtwTemperature == true) {
    Serial.println("Error: Test Failed");
  } else  {
    Serial.println("Test Completed Task Successfully");
  }
  BtwTemperature = true;
  delay(1000);


  Serial.println("Testing Complete.");
  delay(7500);
}
