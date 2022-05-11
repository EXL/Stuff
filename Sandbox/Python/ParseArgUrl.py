#!/usr/bin/env python3

import sys

def print_vars():
    print('U: ' + URL_LINK + '\nF: ' + FILE_NAME + '\nG: ' + GZ_FILE_NAME)

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Error!')
        exit(-1)

    global URL_LINK
    global FILE_NAME
    global GZ_FILE_NAME

    GZ_FILE_NAME = sys.argv[1].split('/')[-1]
    FILE_NAME = GZ_FILE_NAME[:-3]
    URL_LINK = sys.argv[1][:-len(GZ_FILE_NAME)]

    print_vars()
