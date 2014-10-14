#ifndef PGBRIDGE_H
#define PGBRIDGE_H

#import <QObject>

extern QList< QList<int> > _grid;

extern bool test;

void placePiece(const int index, const int player);

#endif // PGBRIDGE_H
