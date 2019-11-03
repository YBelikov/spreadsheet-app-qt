#include "cell.h"

Cell::Cell()
{

}
QTableWidgetItem* Cell::clone() const{
    return new Cell(*this);
}

QString Cell::getText() const{
    return "";
}

QString Cell::getFormula() const{
    return "";
}

void Cell::setFormula(const QString & formula){

}

void Cell::markForRecalculate(){

}
