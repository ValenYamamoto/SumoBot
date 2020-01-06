import pygame
import serial as serial
from time import sleep

pygame.init()
pygame.joystick.init()
joystick = pygame.joystick.Joystick(0)
joystick.init()


ser = serial.Serial('COM5')
print(ser.name)


def deadzone(joy):
    if abs(joy) < 0.09:
        joy = 0
    return joy

def arcade_drive(forward, rotate):
    right = forward + rotate
    left = forward - rotate
    maxx = max(abs(right), abs(left), 100)
    right /= maxx
    left /= maxx
    return int(right * 100), int(left * 100)

def get_y():
    return int(deadzone(-joystick.get_axis(1)) * 100)

def get_x():
    return int(deadzone(joystick.get_axis(4)) * 100)

def get_exit():
    return joystick.get_button(6)

last = [0.1, 0.1]

def loop():
    pygame.event.pump()
    y = get_y()
    x = get_x()

    global last
    
    if last[0] != x or last[1] != y:
        right, left = arcade_drive(y, x)
        print(right, left)
        print()

        ser.write((str(right)+'<'+str(left)+'>').encode())
        
    last = [x, y]
    sleep(0.1)
    ser.reset_input_buffer()

while not get_exit():
    loop()

ser.close()
