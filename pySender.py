##Code Created By Cole Tyler
##Date: November 9, 2018
import serial, datetime, time ## libraries that allow us to use the date/time and allows us to have access to the arduino serial monitor
import socket

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
##f = open("DataBase.txt", "rw") ## opens or creates the notepad file that will be written to
ser = serial.Serial('/dev/ttyACM0', 9600) ## using the serial library, it connects to the arduino 
while ser.isOpen():
  data = ser.readline() ## copies the line is displayed in the arduino serial monitor
  ##data = "gfkjdshfksdjhfdskfgdskjfghdfkgvhfkgjrshngffg"
  data = str(data, 'utf-8') ## converts the data collected into a string so it can be used
  time.sleep(1)
  data = ('{}, {}\n'.format(datetime.datetime.now().strftime('%c'), data))
  
  client.sendto(data.encode(), ("10.0.0.82", 9876))
  
  ##f.write('{}, {}'.format(datetime.datetime.now().strftime('%c'), data)) ## writes the data to notepad and stores the values with the data
  print (data) ## displays the same data that is being sent
  time.sleep(1)
  ##f.readline()

