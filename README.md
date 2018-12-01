# Instructions of How to use the Human Monitor
This Git file contains the instructions of how to use the project code for the human monitor. After buliding and setting of the sensors, switches and collector Raspberry pi to the Adruino Uno. And setting up the Receiving raspberry pi to be connected to a display monitor to display the information collected.

1. The Arduino project code: with the code for the Arduino you must down load the the _Project_Code_ folder onto the collector Raspberry pi and open this file, and have this code be compiled to the arduino off of the collector Raspberry pi that is connected to the Arduino this will have the code be program and installed on the arduino allowing you to collect your data.  

2. The collector Raspberry pi code: For the collector Raspberry pi the code that you have to run and download on the Raspberry pi is the file call _________.py_ this file will take the data that is collected from the Arduino and send it to the receiving Raspberry pi

3. The Receiving Raspberry pi code: The file _____.java_ has to be download and ran on the the other Raspberry pi this program will collect the data that is being sent for the other Raspberry pi, this Receiving Raspberry pi will only receive data if the collector Raspberry pi is sending anything. All the data received will be stored in a datatbase and displayed 

For steps 2 and 3 you can both set up these programs to run when the Raspberry pies turn on allowing these programs to run their programs with manually doing anything. We did this with our group project so it could be more convenient and efficent for our device you can do this by the following steps below.

The Testing Code files:
  - pyMock.py
  - MockCode
  - UnitTesting
  - StubOn
  - StubOff
  
These files are used for testing the hardware and software programs of our group project to demostrate that the device works properly for unit testing, hardware stub testing and _______ testing. All these test files can be found in the _Testing_ folder in the information above.


Creators of the Code:

  Cole Tyler:
    - Project_Code
    - MockCode
    - pyMock.py
    - StubOn
    - StubOff
    - UnitTesting
  
  Pranshu Anand:
    - ______
    - ______
