#include "spreadsheet.h"
#include "cell.h"
#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include "comparator.h"

SpreadSheet::SpreadSheet(QWidget *wgt) : QTableWidget(wgt)
{
    setItemPrototype(new Cell);
    setRowCount(rowCount);
    setColumnCount(columnCount);
    autoRecalc = true;
    for(int i = 0; i < columnCount; ++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)));
        setHorizontalHeaderItem(i, item);
    }
    setCurrentCell(0, 0);
    setSelectionMode(QAbstractItemView::ContiguousSelection);

}

bool SpreadSheet::readFile(const QString& fileName){

    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)){
        quint32 format;
        QDataStream stream(&file);
        stream >> format;
        if(format != formatIdentifier){
            QMessageBox::warning(this, tr("Unexpected format"), tr("Unsupported format file %1.\n%2").arg(file.fileName().arg(file.errorString())));
            return false;
        }
        clear();
        quint16 row, column;
        QString formula;
        while(!stream.atEnd()){
            stream >> row >> column >> formula;
            setFormula(formula, row, column);
        }
        return true;
    }
    QMessageBox::warning(this, tr("Reading error"), tr("Cannot read the file%1.\n%2").arg(file.fileName()).arg(file.errorString()));

    return false;
}

bool SpreadSheet::writeFile(const QString & fileName){
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly)){
        QDataStream stream(&file);
        stream << quint32(formatIdentifier);
        for(int i = 0; i < rowCount; ++i){
            for(int j = 0; j < columnCount; ++j){
                QString formula = getFormula(i, j);
                if(!formula.isEmpty()){
                    stream << quint16(i) << quint16(j) << formula;
                }
            }
        }
        return true;
    }

    QMessageBox::warning(this, tr("Saving error"), tr("Cannot save file %1.\n%2").arg(file.fileName()).arg(file.errorString()));

    return false;
}

void SpreadSheet::goToCell(const QString& cellPosition){

}

QString SpreadSheet::getText(int row, int column) const{
    Cell *cell = getCell(row, column);
    if(cell){
       return cell->text();
    }
    return "";
}

QString SpreadSheet::getFormula(int row, int column) const{
    Cell *cell = getCell(row, column);
    if(cell){
        return cell->getFormula();
    }
    return "";
}

void SpreadSheet::setFormula(const QString& formula, int row, int column){
    Cell *cell = getCell(row, column);
    if(!cell){
        cell = new Cell;
        setItem(row, column, cell);
    }
    cell->setFormula(formula);
}

Cell* SpreadSheet::getCell(int row, int column) const{

    return static_cast<Cell*>(item(row, column));
}

QString SpreadSheet::getCurrentPosition() const{
    return QString(QChar('A' + currentColumn()) + QString::number(currentRow() + 1));
}

QString SpreadSheet::getCurrentFormula() const{
    return getFormula(currentRow(), currentColumn());
}

void SpreadSheet::cut(){
    copy();
    deleteSelected();
}

void SpreadSheet::copy(){

    QTableWidgetSelectionRange toCopyRange = getSelectedRanges();
    QString str;
    qDebug() << toCopyRange.rowCount();
    for(int i = 0; i < toCopyRange.rowCount(); ++i){
        if(i > 0) str += "\n";

        for(int j = 0; j < toCopyRange.columnCount(); ++j){
            if(j > 0)  str += "\t";
            str += getFormula(toCopyRange.topRow() + i, toCopyRange.leftColumn() + j);
            qDebug() << str;
        }
    }
    qDebug() << str;
    QApplication::clipboard()->setText(str);
}

void SpreadSheet::deleteSelected(){

    foreach(QTableWidgetItem* it, selectedItems()){
        delete it;
    }
}

void SpreadSheet::paste(){
    QString str = QApplication::clipboard()->text();
    QTableWidgetSelectionRange range = getSelectedRanges();

    QStringList rowsText = str.split('\n');
    for(int i = 0; i < rowsText.count(); ++i){
        for(int j = 0; j < rowsText[i].count('\t') + 1; ++j){
            QStringList cellsText  = rowsText[i].split('\t');
            setFormula(cellsText[j], range.topRow() + i, range.leftColumn() + j);
        }
    }
}

QTableWidgetSelectionRange SpreadSheet::getSelectedRanges(){
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if(ranges.isEmpty()){
        return QTableWidgetSelectionRange();
    }
    return ranges.first();
}

void SpreadSheet::selectCurrentRow(){
    selectRow(currentRow());
}

void SpreadSheet::selectCurrentColumn(){
    selectColumn(currentColumn());
}

void SpreadSheet::searchNext(const QString& text, Qt::CaseSensitivity cs){
   int i = currentRow();
   int j = currentColumn() + 1;
   while(i < rowCount){
        while(j < columnCount){
            if(getFormula(i, j).contains(text, cs)){
               clearSelection();
               setCurrentCell(i, j);
               activateWindow();
               return;
            }
            ++j;
        }
        j = 0;
        ++i;
   }
    QApplication::beep();
}

void SpreadSheet::searchPrevious(const QString& text, Qt::CaseSensitivity cs){

    int i = currentRow();
    int j = currentColumn() - 1;
    while(i >= 0){
        while(j >= 0){
        if(getFormula(i, j).contains(text, cs)){
            clearSelection();
            setCurrentCell(i, j);
            activateWindow();
            return;
          }
        --j;
       }
        j = columnCount - 1;
        --i;
    }
    QApplication::beep();
}

void SpreadSheet::sort(const Comparator& comparator){

    QTableWidgetSelectionRange range = getSelectedRanges();
    QList<QStringList> rows;
    for(int i = 0; i < range.rowCount(); ++i){
        QStringList row;
        for(int j = 0; j < range.columnCount(); ++j){
            row.append(getFormula(range.topRow() + i, range.leftColumn() + j));
        }
        rows.append(row);
    }
    qStableSort(rows.begin(), rows.end(), comparator);
    for(int i = 0; i < range.rowCount(); ++i){
        for(int j = 0; j < range.columnCount(); ++j){
            setFormula(rows[i][j], range.topRow() + i, range.leftColumn() + j);
        }
    }

    clearSelection();

}

void SpreadSheet::recalculate(){
    for(int i = 0; i < rowCount; ++i){
        for(int j = 0; j < columnCount; ++j){
           if(getCell(i, j)) getCell(i, j)->setValueToBeRecalculated();
        }
    }
    viewport()->update();
}

void SpreadSheet::autoRecalculate(bool autoRec){
    autoRecalc = autoRec;
    if(autoRecalc){
        recalculate();
    }
}

