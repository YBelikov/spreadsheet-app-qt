#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
private:
    QString formula;

public:

    Cell();
    QTableWidgetItem *clone() const;
    void setFormula(const QString&);
    QString getFormula() const;
    QString getText() const;
    void markForRecalculate();

};

#endif // CELL_H
