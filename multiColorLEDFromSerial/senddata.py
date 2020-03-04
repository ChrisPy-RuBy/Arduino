import serial as sl


ser = sl.Serial('/dev/ttyACM0', 9600)
ser.write('255'.encode())
print(ser.readline())
