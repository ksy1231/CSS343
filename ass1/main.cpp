#include <sstream>
#include "turtleProgram.h"

/*
int main() {
    TurtleProgram tp1;
    cout << "tp1: " << tp1 << endl;
    TurtleProgram tp2("F", "10");
    cout << "tp2: " << tp2 << endl;
    TurtleProgram tp3("R", "90");
    tp1 = tp2 + tp3;
    cout << "tp1 now as tp2+tp3: " << tp1 << endl;
    tp1 = tp2 * 3;
    cout << "tp1 now as tp2 * 3: " << tp1 << endl;
    TurtleProgram tp4(tp1);
    cout << "tp4 is a copy of tp1: " << tp4 << endl;
    TurtleProgram tp5("F", "10");
    cout << "tp5: " << tp5 << endl;
    cout << boolalpha;
    cout << "tp2 and tp5 are == to each other: " << (tp2 == tp5) << endl;
    cout << "tp2 and tp3 are != to each other: " << (tp2 != tp3) << endl;
    cout << "index 0 of tp2 is " << tp2.getIndex(0) << endl;
    tp2.setIndex(0, "R");
    tp2.setIndex(1, "90");
    cout << "tp2 after 2 calls to setIndex: " << tp2 << endl;
    cout << "tp2 and tp3 are == to each other: " << (tp2 == tp3) << endl;
    // need to write additional tests for += *=
    cout << "Done." << endl;
    return 0;
}
*/

using namespace std;

string toString(const TurtleProgram& tp) {
    ostringstream out;
    operator<<(out, tp);
    return out.str();
}

template <typename T>
string isOK(const T& got, const T& expected) {
    if (got == expected) {
        return "OK: ";
    } else {
        cout << "    Got " << got << " expected " << expected << endl;
        return "ERR: ";
    }
}


void testBasics() {
    TurtleProgram tp1;
    int length = tp1.getLength();
    cout << isOK(length, 0) << "Length 0 for empty constructor" << endl;
    TurtleProgram tp2("R", "2000");
    cout << isOK(tp2.getLength(), 2) << "Length 2 for 2-param constructor" << endl;
    TurtleProgram tp3(tp2);
    cout << isOK(tp2.getLength(), 2) << "Length 2 for copy constructor" << endl;
    cout << isOK(toString(tp1), string("[]")) << "[] printed for empty constructor" << endl;
    cout << isOK(toString(tp2), string("[R 2000]")) << "[R 2000] printed for 2-param constructor" << endl;
    cout << isOK(toString(tp3), string("[R 2000]")) << "[R 2000] printed for copy constructor" << endl;
    TurtleProgram tp4;
    cout << isOK(tp1 == tp4, true) << "== true for empty tp1 == tp4" << endl;
    TurtleProgram tp5("R", "2000");
    cout << isOK(tp2 == tp5, true) << "== true for 2-param TP tp2 == tp5" << endl;
    TurtleProgram tp6(tp5);
    cout << isOK(tp3 == tp6, true) << "== true for copy constructor TP tp3 == tp6" << endl;
    cout << isOK(tp1 != tp2, true) << "!= empty and 2-param tp1 != tp2" << endl;
    cout << isOK(tp1 != tp3, true) << "!= empty and copy constructor tp1 != tp3" << endl;
    TurtleProgram tp7 = tp1;
    TurtleProgram tp8 = tp2;
    cout << isOK(tp7 == tp1, true) << "= for empty TP using tp7 == tp1" << endl;
    cout << isOK(tp8 == tp2, true) << "= for 2-param TP using tp8 == tp2" << endl;
    TurtleProgram tp9 = tp1 + tp1;
    cout << isOK(tp9.getLength(), 0) << "Length 0 for + empty tp9 = tp1 + tp1" << endl;
    tp9 = tp1 + tp2;
    cout << isOK(tp9.getLength(), 2) << "Length 2 for + empty and 2-param tp9 = tp1 + tp2" << endl;
    cout << isOK(tp9 == tp2, true) << "+ empty and 2-param gives == tp9 == tp2" << endl;
    tp9 = tp2 + tp2 + tp2;
    cout << isOK(tp9.getLength(), 6) << "Length 6 for + 2-param 3 times tp9 = tp2 + tp2 + tp2" << endl;
    cout << isOK(toString(tp9), string("[R 2000 R 2000 R 2000]")) << "Length 6 prints OK toString(tp9)" << endl;
    tp9 = tp2;
    tp9 += tp2;
    cout << isOK(tp9.getLength(), 4) << "Length 4 for += on 2-param tp9 += tp2" << endl;
    tp9 += tp9;
    cout << isOK(tp9.getLength(), 8) << "Length 8 for += on 2-param x 2 tp9 += tp9" << endl;
    tp9 = tp2 * 3;
    cout << isOK(toString(tp9), string("[R 2000 R 2000 R 2000]")) << "Length 6 from * 3 tp9 = tp2 * 3" << endl;
    tp9 = tp2 * 1;
    cout << isOK(tp9 == tp2, true) << "= * 1 gives == tp9 = tp2 * 1, tp9 == tp2" << endl;
    tp9 *= 3;
    cout << isOK(toString(tp9), string("[R 2000 R 2000 R 2000]")) << "Length 6 from *= 3, tp9 *= 3" << endl;
    tp9 = tp2 * 1;
    cout << isOK(tp2.getIndex(0), string("R")) << "index 0, tp9 = tp2 * 1" << endl;
    cout << isOK(tp2.getIndex(1), string("2000")) << "index 1" << endl;
    TurtleProgram tp10(tp2);
    tp10.setIndex(0, "F");
    cout << isOK(tp2 != tp10, true) << "tp10 modified, != anymore" << endl;
    tp10.setIndex(0, "R");
    cout << isOK(tp2 == tp10, true) << "tp10 modified, == now" << endl;
    tp10 = tp10;
    cout << isOK(toString(tp10), string("[R 2000]")) << "self assignment OK for 2" << endl;
    tp10 *= 1;
    cout << isOK(toString(tp10), string("[R 2000]")) << "*1 OK for 2" << endl;
    tp10 *= 5;
    tp10.setIndex(2, "F");
    cout << isOK(toString(tp10), string("[R 2000 F 2000 R 2000 R 2000 R 2000]")) << "*5 modified" << endl;
    tp10 *= 20; // 200
    // cout << tp10.getLength() << endl;
    tp10 *= 1000; // 200k
    // cout << tp10.getLength() << endl;
    tp10 += tp10; // 400 thousand
    // cout << tp10.getLength() << endl;
    cout << isOK(tp10.getLength(), 400000) << "Length 400 thousand!" << endl;
    cout << "Done!" << endl;
}

int main() {
    cout << boolalpha;
    testBasics();
}