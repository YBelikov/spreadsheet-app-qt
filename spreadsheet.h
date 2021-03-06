#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>

class Cell;
class Comparator;

class SpreadSheet : public QTableWidget
{
    Q_OBJECT
private:

    enum {formatIdentifier = 0x7F51C883, rowCount = 999, columnCount = 26};


    Cell *getCell(int, int) const;
    bool autoRecalc;
public slots:

    void cut();
    void copy();
    void paste();
    void deleteSelected();
    void selectCurrentRow();
    void selectCurrentColumn();
    void goToCell(const QString&);
    void searchNext(const QString&, Qt::CaseSensitivity);
    void searchPrevious(const QString&, Qt::CaseSensitivity);
    void recalculate();
    void autoRecalculate(bool);
    void showGrid(bool);

public:

    SpreadSheet(QWidget *wgt = nullptr);
    QTableWidgetSelectionRange getSelectedRanges();
    QString getCurrentPosition() const;
    QString getCurrentFormula() const;
    QString getText(int, int) const;
    QString getFormula(int, int) const;
    void setFormula(const QString&, int, int);
    bool writeFile(const QString&);
    bool readFile(const QString&);
    void sort(const Comparator&);

};

#endif // SPREADSHEET_H
