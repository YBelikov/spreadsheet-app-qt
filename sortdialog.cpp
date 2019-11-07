#include "sortdialog.h"
#include <QtGui>
SortDialog::SortDialog(QWidget* wgt) : QDialog(wgt)
{

    setupUi(this);

    secondaryGroupBox->hide();
    TertiaryGroupBox->hide();
    layout()->setSizeConstraint(QLayout::SetFixedSize);

}

void SortDialog::setColumnRange(QChar first, QChar last){

    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryColumnCombo->clear();

    secondaryColumnCombo->addItem(tr("None"));
    tertiaryColumnCombo->addItem(tr("None"));
    primaryColumnCombo->setMinimumSize(secondaryColumnCombo->sizeHint());
    QChar ch = first;
    while(ch <= last){
        primaryColumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tertiaryColumnCombo->addItem(QString(ch));
        ch = ch.unicode() + 1;
    }
}
