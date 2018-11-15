##Code Created By Cole Tyler
##Date: November 9, 2018
import serial, datetime, time ## libraries that allow us to use the date/time and allows us to have access to the arduino serial monitor

f = open("DataBase.txt", "w") ## opens or creates the notepad file that will be written to
ser = serial.Serial('/dev/ttyACM0', 9600) ## using the serial library, it connects to the arduino 
while ser.isOpen():
  data = ser.readline() ## copies the line is displayed in the arduino serial monitor
  data = str(data, 'utf-8') ## converts the data collected into a string so it can be used
  time.sleep(1)
  f.write('{}, {}'.format(datetime.datetime.now().strftime('%c'), data)) ## writes the data to notepad and stores the values with the data
  print ('{}, {}\n'.format(datetime.datetime.now().strftime('%c'), data)) ## displays the same data that is being written to notepad
  time.sleep(1)
