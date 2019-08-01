import sys

from serial import Serial

def usage():
	print(sys.argv[0] + " [Serial] [file]")
	print("Plays a mupen file.")

def main(serialPort, input):
	port = Serial(serialPort, 250000)
	print(port.read(5))
	with open(input, "rb") as source:
		source.seek(0x400)
		port.write(bytearray([0x0A])) # begin playback
		port.write(bytearray([0x40])) # Nintendo 64 Playback
		port.write(bytearray([0x01])) # One controller

		while True:
			data = source.read(port.read(1)[0])
			if not data:
				port.write(bytearray([0xFF, 0xFF, 0xFF, 0xFF]))
				return
			port.write(data)
			print("f")

if len(sys.argv) == 3:
	main(sys.argv[1], sys.argv[2])
else:
	usage()
