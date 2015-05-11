#!/usr/bin/env python3

import serial
import functions

ser = serial.Serial("/dev/ttyUSB0")
ser.setBaudrate(57600)

functions.reset_pic()
functions.init_ax(ser)

# Attente du start
answer = functions.get_ans(ser)
while answer != "$STRT;":
    answer = functions.get_ans(ser)

# Demande de l'équipe
team = functions.ask_team(ser)

# Déplacement
functions.move_pos(ser,0.1,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.1,0)
    answer = functions.get_ans(ser)

# Rotation
if team == 'g':
    functions.rotate(ser,0.785)
else:
    functions.rotate(ser,5.495)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if team == 'g':
        functions.rotate(ser,0.785)
    else:
        functions.rotate(ser,5.495)
    answer = functions.get_ans(ser)

# Déplacement
if team == 'g':
    functions.move_pos(ser,0.60,0.60)
else:
    functions.move_pos(ser,0.60,-0.60)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    print ("SICKS VALUE : "+str(functions.Sicks))
    if (functions.Sicks==0):
        if team == 'g':
            functions.move_pos(ser,0.60,0.60)
        else:
            functions.move_pos(ser,0.60,-0.60)
    answer = functions.get_ans(ser)

functions.spot_catch_last(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Rotation
#rotate(ser,2.355)
#answer = get_ans(ser)
#while answer != "$DONE;":
#    rotate(ser,2.355)
#    answer = get_ans(ser)

# Déplacement
functions.move_pos(ser,0.2,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.2,0)
    answer = functions.get_ans(ser)

# Rotation
functions.rotate(ser,3.142)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,3.142)
    answer = functions.get_ans(ser)

functions.spot_release(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Déplacement
functions.move_pos(ser,0.5,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.5,0)
    answer = functions.get_ans(ser)

ser.close()
