#include "clcltr.h"

#include <QApplication>
#include<QIcon>
#include<QFile>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Clcltr calculator;
    QIcon calc{ ":/images/calc.png" };

    app.setWindowIcon(calc);
    app.setStyleSheet("QWidget {  color: white;  background-color: rgb(45, 7, 55);   font-family: Sitka Text;  font-size: 20pt;   }   "
        " QPushButton {   background-color: rgba(55, 8, 54, 200);      border: 1px solid rgb(65, 10, 78); }  "
        "QPushButton:hover {background-color: rgba(55, 16, 54, 200); }"
        "QPushButton:pressed {background-color: rgba(55, 23, 54, 200);  }");

    calculator.setWindowTitle("RPN-Калькулятор");
    calculator.setFixedSize(300, 450);
    calculator.show();
    return app.exec();
}
