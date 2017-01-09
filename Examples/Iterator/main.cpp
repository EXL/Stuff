#include "Iterator.h"

#include <iostream>
#include <fstream>

int main() {

    std::ifstream in;

    try {
        in.open("task.in", std::ios::in);
        FileIterator <int>seq(in);

        for (; !seq.over(); ++seq) {
            std::cout << *seq << std::endl;
        }

        in.close();

    } catch (FileNotFoundExcp &e) {
        std::cout << e.getMessage();
        in.close();
    }

    return 0;
}
