#!/usr/bin/env python3

import os, random

COUNT, DATA_X, DATA_Y = 1000, 10, 10

def huge_data(n):
    head = 'unsigned char table_' + n + '[] = {\n'
    for i in range(DATA_X):
        for j in range(DATA_Y):
            head += " " + str(random.randint(0, 255)) + ','
        head += '\n'
    head += '};\n\n'
    return head

def main_stub():
    return '#include "head.hpp"\n\n' \
           'int main() {\n' \
           '\tfunc_0();\n' \
           '\treturn 0;\n' \
           '}\n'

def header_stub():
    body = '#pragma once\n\n'
    for i in range(COUNT):
        body += 'int func_' + str(i) + '();\n'
    return body

def cpp_stub(i):
    return '#include <iostream>\n' \
           '#include "head.hpp"\n\n' \
           'using namespace std;\n\n' \
           + huge_data(str(i)) + \
           'int func_' + str(i) + '() {\n'\
           '\tcout << "Hello from func_' + str(i) + '()!" << endl;\n' \
           + ('\tfunc_' + str(i + 1) + '();\n' if i < COUNT - 1 else '') + \
           '\treturn 0;\n' \
           '}\n'

if __name__ == '__main__':
    os.mkdir('src')
    for i in range(COUNT):
        with open('src/func' + str(i) + '.cpp', 'w') as file:
            file.write(cpp_stub(i))
    with open('src/head.hpp', 'w') as file:
        file.write(header_stub())
    with open('src/main.cpp', 'w') as file:
        file.write(main_stub())
