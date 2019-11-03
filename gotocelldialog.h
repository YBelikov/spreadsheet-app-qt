#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

class QLineEdit;
class QLabel;
class QPushButton;
class QRegExpValidator;

class GoToCellDialog : public QDialog
{
  Q_OBJECT
private:

    QLineEdit *toCellLine;
    QLabel *toCellLabel;
    QPushButton *goToCellButton;
    QPushButton *cancelButton;
    QRegExpValidator *validator;

    void makeWarningBox();

public:

    GoToCellDialog(QWidget *wgt = nullptr);

private slots:
    void goToCell();
    void enableGoToCellButton(const QString&);

signals:
    void goToCell(const QString&);
};

#endif // GOTOCELLDIALOG_H
