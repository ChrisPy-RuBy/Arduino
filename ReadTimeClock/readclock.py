import time
import serial

ser = serial.Serial('/dev/ttyACM0', 57600)

for x in range(100):
    print(ser.readline().decode())
    time.sleep(0.5)
