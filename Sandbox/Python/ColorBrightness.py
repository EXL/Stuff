#!/usr/bin/env python3

def is_light(color):
    return color > 0x007fffff

def get_palette_color(color):
    0xFF - (color >> 16) & 0xFF
    return 0
