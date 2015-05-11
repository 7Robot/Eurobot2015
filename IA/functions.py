#!/usr/bin/env python3

import serial
from time import sleep
import RPi.GPIO as GPIO

Sicks=0

def get_ans(ser):
	global Sicks
	s=ser.read(1).decode("ascii")
	chaine=""
	while s!=';' :
		chaine += s
		s=ser.read(1).decode("ascii")
	chaine += s
	if chaine=="$DSI0;":
		Sicks+=1
	elif chaine=="$DSI1;":
		Sicks+=2
	elif chaine=="$DSI2;":
		Sicks+=4
	elif chaine=="$DSI3;":
		Sicks+=8
	elif chaine=="$DULS;":
		Sicks+=16
	elif chaine=="$RSI0;":
		Sicks-=1
	elif chaine=="$RSI1;":
		Sicks-=2
	elif chaine=="$RSI2;":
		Sicks-=4
	elif chaine=="$RSI3;":
		Sicks-=8
	elif chaine=="$RULS;":
		Sicks-=16
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
	sleep(6) # temps d'init du pic

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

def ask_team(ser):
	command = "$TEAM;"
	ser.write(bytes(command, "ascii"))
	print (command)
	s=get_ans(ser)
	if s=="$YELL;":
		team=1
	else:
		team=-1
	return team

def pince_open(ser):
	command = "$OPES;"
	ser.write(bytes(command, "ascii"))
	print (command)

def pince_close(ser):
	command = "$CLOS;"
	ser.write(bytes(command, "ascii"))
	print (command)

def tube_close(ser):
	command = "$CLTB;"
	ser.write(bytes(command, "ascii"))
	print (command)

def clap_open(ser):
	command = "$CLAO;"
	ser.write(bytes(command, "ascii"))
	print (command)

def clap_close(ser):
	command = "$CLAC;"
	ser.write(bytes(command, "ascii"))
	print (command)

def pop_open(ser):
	command = "$POPO;"# haha !
	ser.write(bytes(command, "ascii"))
	print (command)

def pop_close(ser):
	command = "$POPC;"
	ser.write(bytes(command, "ascii"))
	print (command)

