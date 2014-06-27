#!/usr/bin/env python

import serial
ser = serial.Serial('/dev/tty.usbmodem1a21', 57600)

while True:
	print ser.readline().strip()
