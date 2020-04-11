import datetime
import time
import serial

sensor_ser = serial.Serial('/dev/ttyACM0', 9600)
data = []
while True:
    try:
        line = sensor_ser.readline().decode()
        print(line)
        row = [split.split(":") for split in line.split("  ")]
        data.append(row)
    except ValueError as e:
        print(e)
       

#for x in range(100):
#    try:
#        print(clock_ser.readline().decode())
#    except ValueError as e:
#        pass

