#!/usr/bin/env python3

import serial

from functions import *

ser = serial.Serial("/dev/ttyUSB0")
ser.setBaudrate(57600)

reset_pic()
init_ax(ser)

# Attente du start
answer = get_ans(ser)
while answer != "$STRT;":
    answer = get_ans(ser)

#Demande de l'équipe
team = ask_team(ser)

# Déplacement
move_pos(ser,0.1,0)
answer = get_ans(ser)
while answer != "$DONE;":
    if (answer == "$RSI0;" or answer == "$RSI1;" or answer == "$RSI2;" or answer == "$RSI3;"):
        move_pos(ser,0.1,0)
    answer = get_ans(ser)

# Rotation
if team == 'g':
    rotate(ser,0.785)
else:
    rotate(ser,5.495)
answer = get_ans(ser)
while answer != "$DONE;":
    if team == 'g':
        rotate(ser,0.785)
    else:
        rotate(ser,5.495)
    answer = get_ans(ser)

# Déplacement
if team == 'g':
    move_pos(ser,0.60,0.60)
else:
    move_pos(ser,0.60,-0.60)
answer = get_ans(ser)
while answer != "$DONE;":
    if (answer == "$RSI0;" or answer == "$RSI1;" or answer == "$RSI2;" or answer == "$RSI3;"):
        if team == 'g':
            move_pos(ser,0.60,0.60)
        else:
            move_pos(ser,0.60,-0.60)
    answer = get_ans(ser)

spot_catch_last(ser)
while get_ans(ser) != "$DONE;":
    pass

# Rotation
#rotate(ser,2.355)
#answer = get_ans(ser)
#while answer != "$DONE;":
#    rotate(ser,2.355)
#    answer = get_ans(ser)

# Déplacement
move_pos(ser,0.1,0)
answer = get_ans(ser)
while answer != "$DONE;":
    if (answer == "$RSI0;" or answer == "$RSI1;" or answer == "$RSI2;" or answer == "$RSI3;"):
        move_pos(ser,0.1,0)
    answer = get_ans(ser)

# Rotation
rotate(ser,3.142)
answer = get_ans(ser)
while answer != "$DONE;":
    rotate(ser,3.142)
    answer = get_ans(ser)

spot_release(ser)
while get_ans(ser) != "$DONE;":
    pass

# Déplacement
move_pos(ser,0.5,0)
answer = get_ans(ser)
while answer != "$DONE;":
    if (answer == "$RSI0;" or answer == "$RSI1;" or answer == "$RSI2;" or answer == "$RSI3;"):
        move_pos(ser,0.5,0)
    answer = get_ans(ser)

ser.close()
