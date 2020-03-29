import serial

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
    try: 
        inp = input("Please set motor level between 0-255 or exit with 'd': ")
        if inp == 'd':
            break
        else:
            ser.write(inp.encode())
    except: 
        print('Passing Exception')
        pass

inp = '0'
ser.write(inp.encode())




