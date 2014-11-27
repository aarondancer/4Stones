#ifndef LINE_H
#define LINE_H
#include <iostream>
#include <string>

using namespace std;

enum Direction {none = 0, horizontal = 1, vertical = 2, backwardiag = 3, forwarddiag = 4};

class Line
{
public:
    Line(int pos = -1, Direction d = none, int v = 0, int l = 0, int pc = 0);


    // accessors
    int startingPos() const;
    int value() const;
    int length() const;
    int pieces() const;
    Direction direction() const;

    // methods
    void initialize(int pos, Direction d, int v = 0, int l = 0, int pc = 0);
    void addPiece(const int piece);
    bool isFull() const;
    string directionToString() ;

    // operator overloads
    void operator = (const Line &line);
    bool operator == (const Line &line) const;
    bool operator > (const Line &line) const;
    bool operator < (const Line &line) const;

private:
    int _startingPos;
    int _value;
    int _length;
    int _pieces;
    Direction _dir;
};

#endif // LINE_H
