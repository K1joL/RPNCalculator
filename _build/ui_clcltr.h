/********************************************************************************
** Form generated from reading UI file 'clcltr.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLCLTR_H
#define UI_CLCLTR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Clcltr
{
public:

    void setupUi(QWidget *Clcltr)
    {
        if (Clcltr->objectName().isEmpty())
            Clcltr->setObjectName(QString::fromUtf8("Clcltr"));
        Clcltr->resize(800, 600);

        retranslateUi(Clcltr);

        QMetaObject::connectSlotsByName(Clcltr);
    } // setupUi

    void retranslateUi(QWidget *Clcltr)
    {
        Clcltr->setWindowTitle(QCoreApplication::translate("Clcltr", "Clcltr", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Clcltr: public Ui_Clcltr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLCLTR_H
