#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
private:

    mutable QVariant cachedValue;
    mutable bool toBeRecalculated;
    void setData(int role, const QVariant &value);
    QVariant data(int role) const;
    QVariant value() const;
    QVariant evalExpression(const QString&, int&) const;
    QVariant evalTerm(const QString&, int&) const;
    QVariant evalFactor(const QString&, int&) const;
public:

    Cell();
    QTableWidgetItem *clone() const;
    void setFormula(const QString&);
    QString getFormula() const;
    void setValueToBeRecalculated();

};

#endif // CELL_H
