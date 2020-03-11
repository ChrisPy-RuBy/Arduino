import datetime
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)
data = []
while True:
    try:
        line = ser.readline().decode()
        print(line)
        row = [split.split(":") for split in line.split("  ")]
        data.append(row)
    except ValueError as e:
        print(e)
        
