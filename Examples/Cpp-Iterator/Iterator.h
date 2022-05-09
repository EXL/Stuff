#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include <fstream>

class FileNotFoundExcp {
private:
    const std::string message;

public:
    FileNotFoundExcp(const std::string &string) : message(string) { }
    std::string getMessage() const { return message; }
};

template <typename TypeOfFile>
class FileIterator {
    private:
        TypeOfFile value;
        std::ifstream *input;
    public:
        FileIterator(std::ifstream& in) {
            if (in.fail()) {
                throw FileNotFoundExcp("File not found!\n");
            }

            input = &in;
            *input >> value;
        }

        ~FileIterator() { }

        void next() {
            *input >> value;
        }

        void operator++() { // For ++it
            next();
        }

        void operator++(int) { // For it++
            operator++();
        }

        bool over() {
            return !(*input);
        }

        TypeOfFile operator*() {
            return value;
        }
};

#endif //ITERATOR_H
