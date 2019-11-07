#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "ui_dialog.h"
#include "comparator.h"

class SortDialog : public QDialog, private Ui::Dialog
{
    Q_OBJECT
private:
    Comparator comp;
public:

    SortDialog(QWidget *wgt = nullptr);
    void setColumnRange(QChar, QChar);
    Comparator getComparator(){return comp;}

 };

#endif // SORTDIALOG_H
