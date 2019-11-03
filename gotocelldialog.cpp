#include "gotocelldialog.h"
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QBoxLayout>

GoToCellDialog::GoToCellDialog(QWidget *wgt) : QDialog(wgt)
{
    toCellLabel = new QLabel("To cell");
    toCellLine = new QLineEdit;
    toCellLabel->setBuddy(toCellLine);
    goToCellButton = new QPushButton("Go to cell");
    goToCellButton->setEnabled(false);
    cancelButton = new QPushButton("Cancel");
    QRegExp expr("[A-Za-z][1-9][0-9]\\{0, 2}");
    validator = new QRegExpValidator;
    validator->setRegExp(expr);
    connect(toCellLine, SIGNAL(textChanged(const QString&)), this, SLOT(enableGoToCellButton(const QString&)));
    connect(goToCellButton, SIGNAL(clicked()), this, SLOT(goToCell()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(toCellLabel);
    topLayout->addWidget(toCellLine);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(goToCellButton);
    bottomLayout->addWidget(cancelButton);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);
}

void GoToCellDialog::enableGoToCellButton(const QString& text){
    goToCellButton->setEnabled(!text.isEmpty());
}

void GoToCellDialog::goToCell(){
    int pos = 0;
    QString text = toCellLine->text();
    validator->validate(text, pos) == QValidator::Acceptable || QValidator::Intermediate ? emit goToCell(text) : makeWarningBox();
}

void GoToCellDialog::makeWarningBox(){

    this->hide();
    int result = QMessageBox::warning(nullptr, "Input validation",
                                                "Input is invalid.\n"
                                                " Use the following format: {column letter}{row number}"
                                                " without curly braces and white spaces.\n"
                                               "Columns range is A-Z, rows range is 1-999",
                                      QMessageBox::Ok | QMessageBox::No | QMessageBox::Cancel);
    if(result == QMessageBox::Ok){
        this->show();
    }else{
        this->close();
    }

}
