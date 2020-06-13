import sys
import serial
import time
import matplotlib.pyplot as plt
import csv
import datetime 


"""Basic serial port parser for arduino
"""

ser = serial.Serial('/dev/ttyACM0', 9600)
time.sleep(2)

data = []

try: 
    counter = 0
    filename = './sensortest.csv'
    with open(filename, 'w') as f:
        writer = csv.writer(f)
        while counter < 10:
            line = ser.readline()
            value = line.decode('utf-8').strip()
            now = datetime.datetime.now().isoformat()
            print(now, value)
            row = [now, value]
            writer.writerow(row)
            data.append(row)
            counter += 1
finally:
    ser.close()


x, y = [row for row in zip(*data)]

plt.plot(x, y)
plt.show()


