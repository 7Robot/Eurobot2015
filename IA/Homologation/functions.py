#!/usr/bin/env python3

import serial
from time import sleep
import RPi.GPIO as GPIO

def get_ans(ser):
	s=ser.read(1).decode("ascii")
	chaine=""
	while s!=';' :
		chaine += s
		s=ser.read(1).decode("ascii")
	chaine += s
	print ("    "+chaine)
	sleep(0.1)
	return chaine

def move_pos(ser,x,y):
	angle="0"
	command = "$MOVE,"+str(x)+","+str(y)+","+angle+";"
	ser.write(bytes(command, "ascii"))
	print (command) #affiche dans la console

def rotate(ser,angle):
	command = "$ANGL,"+str(angle)+";"
	ser.write(bytes(command, "ascii"))
	print (command) #affiche dans la console

def reset_pic():
	GPIO.setmode(GPIO.BCM)
	GPIO.setup(17, GPIO.OUT)
	GPIO.output(17, True)
	sleep(2)
	GPIO.output(17, False)
	sleep(4) # temps d'init du pic

def spot_catch(ser): # attraper un spot
	command = "$CHAR;"
	ser.write(bytes(command, "ascii"))
	print (command)

def init_ax(ser):
	command = "$AXIN;"
	ser.write(bytes(command, "ascii"))
	print (command)


def spot_catch_last(ser):
	command = "$CHAL;"
	ser.write(bytes(command, "ascii"))
	print (command)

def spot_release(ser):
	command = "$RELE;"
	ser.write(bytes(command, "ascii"))
	print (command)

def close_claws(ser):
        command = "$CLOS;"
	ser.write(bytes(command, "ascii"))
	print (command)

def ask_team(ser):
	command = "$TEAM;"
	ser.write(bytes(command, "ascii"))
	print (command)
	s=get_ans(ser)
	if s=="$YELL;":
		team='y'
	else:
		team='g'
	return team
