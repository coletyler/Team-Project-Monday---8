##Code Created By Pranshu Anand
##Date: November 9, 2018

import serial, datetime, time ## libraries that allow us to use the date/time and allows us to have access to the arduino serial monitor
import socket
import string 
from random import *## importing random string inputs values. 

min_char = 0 ## minimum characters to inputs.
max_char = 12 ## maximum characters to inputs. 
allchar = string.ascii_letters + string.digits + string.punctuation ## allowed to input letters, numbers, and punctuation. 
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while 1:
    data = "".join(choice(allchar) for x in range(randint(min_char, max_char))) ## storinging the input string to variable called data. 
    time.sleep(1)
    data = '{}, {}\n'.format(datetime.datetime.now().strftime('%c'), data)
    client.sendto(data.encode(), ("10.0.0.82", 9876))
     print (data) ## displays the same data that is being sent
    time.sleep(1)
