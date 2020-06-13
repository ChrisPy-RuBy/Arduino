import serial
import datetime


ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    row = ser.readline()
    print(datetime.datetime.now().isoformat(), row)
