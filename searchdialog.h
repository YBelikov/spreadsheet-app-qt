#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

class QLabel;
class QCheckBox;
class QPushButton;
class QLineEdit;

class SearchDialog : public QDialog
{
    Q_OBJECT

private:

    QLabel  *searchForLabel;
    QLineEdit *searchForLine;
    QCheckBox *caseSensitivity;
    QCheckBox *searchBackward;

    QPushButton *searchButton;
    QPushButton *cancelButton;

public:

    SearchDialog(QWidget *wgt = nullptr);
public slots:
    void enableSearchButton(const QString&);
   // void close();
    void search();

signals:

    void searchNext(const QString&, Qt::CaseSensitivity);
    void searchPrevious(const QString&, Qt::CaseSensitivity);
};

#endif // SEARCHDIALOG_H
