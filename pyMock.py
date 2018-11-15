##Code Created By Cole Tyler
##Date: November 9, 2018
##This code if used for testing the mock Arduino code
import serial, datetime, time ## libraries that allow us to use the date/time and allows us to have access to the arduino serial monitor

try: ## Checks if the the Text File is opened/Created
  f = open("DataBase.txt", "w") ## opens or creates the notepad file that will be written to
  time.sleep(1)
  print ('File is Opened/Created Successfully') ## informs us if task was completed
except:
  print ('Error detected: File was Opened/Created') ## informs us if task was not completed

try: ## Checks if the python connects the Arduino's Serial Monitor
  ser = serial.Serial('/dev/ttyACM0', 9600) ## using the serial library, it connects to the arduino 
  ser.isOpen()
  time.sleep(1)
  print ('Python is connected to Serial Successfully') ## informs us if task was completed
except:
  print ('Error detected: Python is not connected to Serial') ## informs us if task was not completed

try: ## Checks if the data was stored to the Text file
  while ser.isOpen():
    data = ser.readline() ## copies the line is displayed in the arduino serial monitor
    data = str(data, 'utf-8') ## converts the data collected into a string so it can be used
    f.write('{}, {}'.format(datetime.datetime.now().strftime('%c'), data)) ## writes the data to notepad and stores the values with the data
    print ('Data was Stored Successfully') ## informs us if task was completed
  time.sleep(1)
 ## print ('Data was Stored Successfully') ## informs us if task was completed
except:
  print ('Testing is Done') ## informs us if task was not completed
