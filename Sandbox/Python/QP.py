#!/usr/bin/python
# -*- coding: utf-8 -*-

import quopri
import sys

arg = str(sys.argv[1])

if arg.startswith('='):
    print(str(quopri.decodestring(arg).decode('utf8')))
else:
    string = str(quopri.encodestring(bytes(arg, 'utf8')))
    print(string[2:-1])

