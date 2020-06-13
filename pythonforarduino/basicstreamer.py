import serial
import datetime


ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    print(datetime.datetime.now().isoformat(), ser.readline())
