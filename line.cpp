#include "line.h"

// constructors
Line::Line(int pos, Direction d, int v, int l, int pc) {
    initialize(pos, d, v, l, pc);
}


// accessors
int Line::startingPos() const {return _startingPos;}
int Line::value() const {return _value;}
int Line::length() const {return _length;}
int Line::pieces() const {return _pieces;}
Direction Line::direction() const {return _dir;}

// methods
void Line::initialize(int pos, Direction d, int v, int l, int p) {
    _startingPos = pos;
    _dir = d;
    _value = v;
    _length = l;
    _pieces = p;
}

void Line::addPiece(const int piece) {
    if (piece != 0) {
        _value += piece;
        _pieces++;
    }
    _length++;
}

bool Line::isFull() const {return (_pieces == _length);}

string Line::directionToString() {
    std::string dir;

    if (_dir == horizontal) dir = "horizontal";
    else if(_dir == vertical) dir = "vertical";
    else if(_dir == backwardiag) dir = "backward diagonal";
    else if(_dir == forwarddiag) dir = "forward diagaonal";

    return dir;
}


// operator overloads
void Line::operator = (const Line &line) {
    _startingPos = line.startingPos();
    _dir = line.direction();
    _value = line.value();
    _length = line.length();
    _pieces = line.pieces();
}

bool Line::operator == (const Line &line) const {return (_value == line.value());}

bool Line::operator > (const Line &line) const {return (_value > line.value());}

bool Line::operator < (const Line &line) const {return (_value < line.value());}
