import serial
import datetime


with serial.Serial('/dev/ttyACM0', 9600) as ser:
    while True:
        row = ser.readline()
        print(datetime.datetime.now().isoformat(), row)
