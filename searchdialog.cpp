#include "searchdialog.h"
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>

SearchDialog::SearchDialog(QWidget *wgt) : QDialog(wgt)
{
    searchForLabel = new QLabel("&Search for: ");
    searchForLine = new QLineEdit;
    searchButton = new QPushButton(tr("&Search"));
    cancelButton = new QPushButton(tr("&Cancel"));
    searchBackward = new QCheckBox(tr("&Search backward"));
    caseSensitivity = new QCheckBox(tr("&Case sensitive"));
    searchForLabel->setBuddy(searchForLine);
    searchButton->setEnabled(false);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(searchForLabel);
    topLayout->addWidget(searchForLine);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLayout);
    leftLayout->addWidget(searchBackward);
    leftLayout->addWidget(caseSensitivity);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(searchButton);
    rightLayout->addWidget(cancelButton);
    rightLayout->addStretch();

    QHBoxLayout *searchDialogMainLayout = new QHBoxLayout;
    searchDialogMainLayout->addLayout(leftLayout);
    searchDialogMainLayout->addLayout(rightLayout);
    setLayout(searchDialogMainLayout);
    setWindowTitle(tr("Search"));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(searchForLine, SIGNAL(textChanged(const QString&)), this, SLOT(enableSearchButton(const QString&)));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    setFixedSize(sizeHint());
}

void SearchDialog::enableSearchButton(const QString& text){
    searchButton->setEnabled(!text.isEmpty());
}

void SearchDialog::search(){
    QString text = searchForLine->text();
    Qt::CaseSensitivity cs = caseSensitivity->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if(searchBackward->isChecked()){
        emit searchPrevious(text, cs);
    }
    emit searchNext(text, cs);
}
