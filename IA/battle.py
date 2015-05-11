#!/usr/bin/env python3

import serial
import functions
from time import sleep
from math import *

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
functions.move_pos(ser,-0.2,0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.2,0)
    answer = functions.get_ans(ser)

# Rotation
functions.rotate(ser,(6.283+team*0.275)%6.283)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,(6.283+team*0.275)%6.283)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,-0.43,-team*0.07)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.43,-team*0.07)
    answer = functions.get_ans(ser)

# On ferme l'attrape verre
functions.pop_close(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# On ouvre les pinces
functions.pince_open(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Rotation
functions.rotate(ser,(6.283+team*1.68)%6.283)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,(6.283+team*1.68)%6.283)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,-0.46,team*0.23)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.46,team*0.23)
    answer = functions.get_ans(ser)

# On attrape un spot
functions.spot_catch(ser)
answer = functions.get_ans(ser)
while answer != "$DONE;" and answer != "$FAAX;":
    answer = functions.get_ans(ser)

# Rotation
functions.rotate(ser,(6.283+team*3.8)%6.283)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,(6.283+team*3.8)%6.283)
    answer = functions.get_ans(ser)

# On ouvre l'attrape verre
functions.pop_open(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Déplacement
functions.move_pos(ser,0.06,team*0.695)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.06,team*0.695)
    answer = functions.get_ans(ser)

# On ferme l'attrape verre
functions.pop_close(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Rotation
functions.rotate(ser,(6.283+team*2.1)%6.283)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,(6.283+team*2.1)%6.283)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,0.23,team*0.4)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.23,team*0.4)
    answer = functions.get_ans(ser)

# Rotation
functions.rotate(ser,(6.283+team*1.4)%6.283)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,(6.283+team*1.4)%6.283)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,0.25,team*0.54)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.25,team*0.54)
    answer = functions.get_ans(ser)

# On attrape un spot
functions.spot_catch(ser)
answer = functions.get_ans(ser)
while answer != "$DONE;" and answer != "$FAAX;":
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,0.26,team*0.62)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.26,team*0.62)
    answer = functions.get_ans(ser)

# On attrape un spot
functions.spot_catch(ser)
answer = functions.get_ans(ser)
while answer != "$DONE;" and answer != "$FAAX;":
    answer = functions.get_ans(ser)

# On ferme les pinces
functions.pince_close(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# On ouvre les claps
functions.clap_open(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Rotation
functions.rotate(ser,(6.283+team*1.65)%6.283)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,(6.283+team*1.65)%6.283)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,0.24,team*0.70)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.24,team*0.70)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,0.23,team*0.72)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.23,team*0.72)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,0.22,team*0.74)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0.22,team*0.74)
    answer = functions.get_ans(ser)

# Rotation
functions.rotate(ser,(6.283+team*3.1)%6.283)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,(6.283+team*3.1)%6.283)
    answer = functions.get_ans(ser)

# On ouvre les pinces
functions.pince_open(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Déplacement
functions.move_pos(ser,0,team*0.74)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,0,team*0.74)
    answer = functions.get_ans(ser)

# On ferme les claps
functions.clap_close(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Déplacement
functions.move_pos(ser,-0.3,team*0.76)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.3,team*0.76)
    answer = functions.get_ans(ser)

# On ouvre les claps
functions.clap_open(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Déplacement
functions.move_pos(ser,-0.5,team*0.78)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.5,team*0.78)
    answer = functions.get_ans(ser)

# On attrape le dernier spot
functions.spot_catch_last(ser)
answer = functions.get_ans(ser)
while answer != "$DONE;" and answer != "$FAAX;":
    answer = functions.get_ans(ser)

# On ferme les claps
functions.clap_close(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Déplacement
functions.move_pos(ser,-0.625,team*0.80)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.625,team*0.80)
    answer = functions.get_ans(ser)

# On lache tout
functions.spot_release(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Déplacement
functions.move_pos(ser,-0.40,team*0.78)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.40,team*0.78)
    answer = functions.get_ans(ser)

# Rotation
functions.rotate(ser,(6.283+team*4.71)%6.283)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,(6.283+team*4.71)%6.283)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,-0.40,0.0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.40,0.0)
    answer = functions.get_ans(ser)

# Rotation
functions.rotate(ser,3.14)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,3.14)
    answer = functions.get_ans(ser)

# Déplacement
functions.move_pos(ser,-0.1,0.0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.1,0.0)
    answer = functions.get_ans(ser)

# Rotation
functions.rotate(ser,3.14)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    functions.rotate(ser,3.14)
    answer = functions.get_ans(ser)

# On ouvre l'attrape verre
functions.pop_open(ser)
while functions.get_ans(ser) != "$DONE;":
    pass

# Déplacement
functions.move_pos(ser,-0.5,0.0)
answer = functions.get_ans(ser)
while answer != "$DONE;":
    if (functions.Sicks==0):
        functions.move_pos(ser,-0.5,0.0)
    answer = functions.get_ans(ser)

ser.close()
