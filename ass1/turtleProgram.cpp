//
// Created by 김수연 on 10/1/18.
//

#include "turtleProgram.h"

// create object
TurtleProgram::TurtleProgram() {
    size = 0;
    strArr = new string[size];
}

// create object
TurtleProgram::TurtleProgram(TurtleProgram &&tp) {
    size = tp.size;
    strArr = new string[size];
    for(int i = 0; i < size; i++) {
        strArr[i] = tp.strArr[i];
    }
}

// create object with two strings
TurtleProgram::TurtleProgram(string direction, string num) {
    size = 2;
    strArr = new string[size];
    strArr[0] = direction;
    strArr[1] = num;
}

// copy object
TurtleProgram::TurtleProgram(TurtleProgram &tp) {
    size = tp.size;
    strArr = new string[size];
    for (int i = 0; i < size; i++) {
        strArr[i] = tp.strArr[i];
    }
}

// delete array
TurtleProgram::~TurtleProgram() {
    if(strArr != NULL) {
        delete[] strArr;
    }
}

// print output
ostream &operator<<(ostream &out, const TurtleProgram &tp) {
    out << "[";
    for(int i = 0; i < tp.size; i++) {
        out << tp.strArr[i];
        if(i + 1 < tp.size) {
            out << " ";
        }
    }
    out << "]";
    return out;
}

// calculate addiction
TurtleProgram TurtleProgram::operator+(const TurtleProgram &tp) const {
    TurtleProgram add;
    add.size = tp.size + size;
    add.strArr = new string[add.size];
    for(int i = 0; i < size; i++) {
        add.strArr[i] = strArr[i];
    }
    for(int i = 0; i < tp.size; i++) {
        add.strArr[i + size] = tp.strArr[i];
    }
    return add;
}

// calculate multiplication
TurtleProgram TurtleProgram::operator*(int num) const {
    TurtleProgram mult;
    mult.size = size * num;
    mult.strArr = new string[mult.size];
    for(int i = 0; i < mult.size; i++) {
        mult.strArr[i] = strArr[i % size];
    }
    return mult;
}

// add object by making new array
TurtleProgram &TurtleProgram::operator+=(const TurtleProgram &tp) {
    int newSize = size + tp.size;
    string *newStrArr = new string[newSize];
    for(int i = 0; i < size; i++) {
        newStrArr[i] = strArr[i];
    }
    for(int i = 0; i < tp.size; i++) {
        newStrArr[size + i] = tp.strArr[i];
    }
    size = newSize;
    strArr = newStrArr;
    return *this;
}

// multiply object by creating new array
TurtleProgram &TurtleProgram::operator*=(const int num) {
    int newSize = size * num;
    string *newStrArr = new string[newSize];
    for(int i = 0; i < newSize; i++) {
        newStrArr[i] = strArr[i % size];
    }
    size = newSize;
    strArr = newStrArr;
    return *this;
}

// check that they are same
bool TurtleProgram::operator==(const TurtleProgram &tp) const {
    bool isEqual = true;
    if(tp.size != size) {
        isEqual = false;
    } else {
        for(int i = 0; i < size; i++) {
            if(tp.strArr[i] != strArr[i]) {
                isEqual = false;
                break;
            }
        }
    }
    return isEqual;
}

// check that they are not same
bool TurtleProgram::operator!=(const TurtleProgram &tp) const {
    return !(this == &tp);
}

// check whether they are same or not, delete array and create new array
TurtleProgram &TurtleProgram::operator=(const TurtleProgram &tp) {
    if(this == &tp) {
        return *this;
    }
    if(strArr != 0) {
        delete[] strArr;
        size = 0;
    }
    size = tp.size;
    strArr = new string[size];
    for(int i = 0; i < size; i++) {
        strArr[i] = tp.strArr[i];
    }
    return *this;
}

// return index of string by receiving integer
string TurtleProgram::getIndex(int num) {
    return strArr[num];
}

// set index in array based on integer and string
void TurtleProgram::setIndex(int num, string str) {
    this->strArr[num] = str;
}

// return length of array
int TurtleProgram::getLength() {
    return size;
}
