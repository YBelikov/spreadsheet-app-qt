#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>
#include "ui_dialog.h"

class SortDialog : public QDialog, public Ui::Dialog
{
    Q_OBJECT
public:

    SortDialog(QWidget *wgt = nullptr);

 };

#endif // SORTDIALOG_H
