from serial import Serial

port = Serial("/dev/ttyUSB0", 500000)

port.write(bytearray([42]))
port.write(bytearray(range(0, 32)))
while True:
	for x in range(0, 256):
		port.read()
		port.write(bytearray([x]))
		print("Written: " + str(x))
		#
		# while port.in_waiting == 0:
		# 	pass
		#
		# port.read()
