#!/usr/bin/env python

from log_lib import *

import serial
ser = serial.Serial('/dev/tty.usbmodem1a21', 57600)

while True:
	line = ser.readline().strip()
	
	parsed = parse_line(line)
	if len(parsed) == 0:
		print line
	else:
		print parsed[0] + " :\t", format_bits(parsed[1])

