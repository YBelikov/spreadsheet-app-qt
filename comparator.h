#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <QStringList>

class Comparator
{
private:

    enum{numberOfKeys = 3};
    int keys[numberOfKeys];
    bool ascendingOrder[numberOfKeys];

public:

    bool operator()(const QStringList& row1, const QStringList& row2);
    Comparator();
};

#endif // COMPARATOR_H
