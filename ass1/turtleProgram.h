//
// Created by 김수연 on 10/1/18.
//

#ifndef ASS1_TURTLE_H
#define ASS1_TURTLE_H

#include <string>
#include <iostream>
using namespace std;

class TurtleProgram{
    friend ostream& operator<<(ostream &out, const TurtleProgram &tp);
public:
    // 0 parameter constructor
    TurtleProgram();
    // 1 parameter constructor
    TurtleProgram(TurtleProgram &&tp);
    // 2 parameters constructor
    TurtleProgram(string direction, string num);
    // copy constructor
    TurtleProgram(TurtleProgram &tp);
    // destructor
    ~TurtleProgram();

    // Operator Overloads
    TurtleProgram operator+(const TurtleProgram &tp) const;
    TurtleProgram operator*(int num) const;

    TurtleProgram&operator+=(const TurtleProgram &tp);
    TurtleProgram&operator*=(int num);

    bool operator==(const TurtleProgram &tp) const;
    bool operator!=(const TurtleProgram &tp) const;

    TurtleProgram& operator=(const TurtleProgram& tp);

    string getIndex(int num);
    void setIndex(int num, string str);
    int getLength();

private:
    int size;
    string *strArr;
};

#endif //ASS1_TURTLE_H
