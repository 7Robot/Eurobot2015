# Functions to make the bot moving efficiently

A python program that sends commands to the bot enslavement program to make the bot moving.

## Required

Three global variables :

 * X position
 * Y Position
 * Angle of direction (Right: 0, Top; 90, Left: 180, Bottom: 270)

## Inputs

 * Current position (see previous section) 
 * Final position using the three previous parameters
 * List of geometries (rectangles) which represents areas where the bot can't go (Stairs, Opponent bot, objects on the table...)

## Outputs

Moves the bot from A to B respecting the non-go areas using bezier curves.
Stops and fail if an object is detected on the path (need to relaunch the command from current position to final position wih updated opponent bot position)