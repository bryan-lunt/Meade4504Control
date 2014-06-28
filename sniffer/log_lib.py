#!/usr/bin/env python

def parse_line(packet):
	try:
                count, data = packet.split(" : ",1)
		bits = data #some conversion here?
                return count, bits
        except:
                return packet 

def format_43(bits):
	outline = ""
	outline += "" + bits[0] + " " #start bit
	outline += "" + "".join(bits[1:9]) + "\n"
	outline += "\t" + format_bits("X" + bits[10:])
	return outline

def format_67(bits):
	outline = ""
	outline += format_bits(bits[:34])
	outline += "\n\t" + format_bits("X" + bits[34:])
	return outline


def format_bits(some_bits):
	
	if len(some_bits) == 43:
		return format_43(some_bits);
	elif len(some_bits) == 67:
		return format_67(some_bits);
	
	outline = ""
	
	for i in range(len(some_bits)):
		outline += some_bits[i];
		if (i % 8 == 0):
			outline += " "

	
	return outline


