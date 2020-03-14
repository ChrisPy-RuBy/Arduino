import time
import serial

ser = serial.Serial('/dev/ttyACM0', 57600)

for x in range(100):
    try:
        print(ser.readline().decode())
    except ValueError as e:
        pass
