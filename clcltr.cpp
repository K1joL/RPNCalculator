#include "clcltr.h"
#include "ui_clcltr.h"
#include <QString>
#include <QRegularExpression>
#include <QFile>
#include <QIcon>

using namespace std;

qint8 countDot = 0;

QIcon backspace {":/images/bckspce.png"};

Clcltr::Clcltr(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Clcltr)
{
    ui->setupUi(this);

    displaystring = new QLabel("");
    displaystring->setMinimumSize(150,30);
    displaystring->setAlignment(Qt::AlignRight|Qt::AlignTrailing);
    displaystring->setText("0");
    displaystring->setStyleSheet(QString("font-size: %1px").arg(40));

    displayexp = new QLabel("");
    displayexp->setMinimumSize(150,20);
    displayexp->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignBottom);
    displayexp->setStyleSheet(QString("font-size: %1px").arg(30));

    QChar aButtons[4][4] = {
        {'7', '8', '9', '/'},
        {'4', '5', '6', '*'},
        {'1', '2', '3', '-'},
        {'0', '.', '=', '+'}
    };
    QPushButton *bckspace = new QPushButton();
    bckspace->setIcon(QIcon(":/images/bckspce.png"));
    bckspace->setIconSize(QSize(45,45));
    bckspace->setMinimumSize(60, 60);
    connect(bckspace, SIGNAL(clicked()), this, SLOT(slotBckspaceClicked()));

    QGridLayout *myLayout = new QGridLayout;
    myLayout->addWidget(displayexp, 0, 0, 1, 4);
    myLayout->addWidget(displaystring, 1 , 0, 1, 4);
    myLayout->addWidget(createButton("CE"), 2, 1);
    myLayout->addWidget(bckspace, 2, 2);
    myLayout->addWidget(createButton("%"), 2, 3);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            myLayout->addWidget(createButton(aButtons[i][j]), i + 3, j);
        }
    }

    myLayout->setSpacing(6);
    setLayout(myLayout);
}
QPushButton *Clcltr::createButton ( const QString &str)
{
    QPushButton *pcmd = new QPushButton(str);
    pcmd->setMinimumSize(60, 60);
    connect(pcmd, SIGNAL(clicked()), this, SLOT(slotButtonClicked()));

    return pcmd;
}

void fontSize(QString text, QLabel *displaystring, QLabel *displayexp)
{
    int size = 40;
    if (text.size() > 10)
    {
        size = 30;
        if(text.size()  > 15)
        {
            size = 20;
            if(text.size()  > 25)
            {
                size = 18;
                displaystring->setStyleSheet(QString("font-size: %1px").arg(size));
            }
            displaystring->setStyleSheet(QString("font-size: %1px").arg(size));
        }
        displaystring->setStyleSheet(QString("font-size: %1px").arg(size));
    }else
        displaystring->setStyleSheet(QString("font-size: %1px").arg(size));
    displayexp->setStyleSheet(QString("font-size: %1px").arg(14));
    displayexp->setStyleSheet("color: #8a7893");
}
void Clcltr::slotBckspaceClicked()
{
    QString str = ((QPushButton *)sender())->text();
    QString text = displaystring->text();
    fontSize(text, displaystring, displayexp);

    if (text.endsWith("."))
         countDot--;
     text.chop(1);
     displaystring->setText(text);
     if (!text.length())
     {
         displaystring->setText("0");
     }
     return;
}
void Clcltr::slotButtonClicked()
{
    rpn* CalculatorQT = new rpn;
    QString str = ((QPushButton*)sender())->text();
    QString text = displaystring->text();

    fontSize(text, displaystring, displayexp);

    if (text == "Ошибка. Нельзя делить на ноль." || text == "Ошибка. Некоректный ввод.")
        str = "CE";

    if (str == "CE")
    {
        displaystring->setText("0");
        displayexp->setText("");
        countDot = 0;
        displaystring->setStyleSheet(QString("font-size: %1px").arg(40));
        return;
    }

    if (displayexp->text().endsWith("=") && (!(str == "+" || str == "-" || str == "*" || str == "/" || str == "%" || str == "=")))
    {
        text = "0";
        displayexp->setText("");
        countDot = 0;
        displaystring->setText(text);
    }
    else
        displayexp->setText("");

    if ((str == "." || str == "+" || str == "-" || str == "*" || str == "/" || str == "%") && text == "0")
    {
        text = "0";
        text += str;
        if (str == ".")
            countDot++;
    }

    if (text == "0")
    {
        text = "";
    }

    if (str != "=")
    {
        if (((str == '+') || (str == '-') || (str == '*') || (str == '/') || (str == '%')) &&
            (text.endsWith('+') || text.endsWith('-') || text.endsWith('*') || text.endsWith('/') || text.endsWith('%') || text.endsWith('.')))
        {
            if (text.endsWith('.'))
            {
                countDot--;
            }
            text.chop(1);
            text += str;
        }
        else
        {
            if (str == ".")
            {
                if (!countDot)
                {
                    if ((text.endsWith('+') || text.endsWith('-') || text.endsWith('*') || text.endsWith('/') || text.endsWith('%')))
                    {
                        text += "0";
                        text += str;
                        countDot++;
                    }
                    else
                    {
                        countDot++;
                        text += str;
                    }
                }
                else
                    displaystring->setText(text);
            }
            else
            {
                if ((str == '+') || (str == '-') || (str == '*') || (str == '/') || (str == '%'))
                {
                    text += str;
                    if (countDot)
                        countDot--;
                }
                else
                    text += str;
            }
        }
    }
    else if (text.size())
    {
        if (text.endsWith('+') || text.endsWith('*') || text.endsWith('/') || text.endsWith('%')) { text.chop(1); } // Удаление последнего символа операции
        countDot = 0;
        text += "=";
        displayexp->setText(text); // вывести на экран выражение
        text = CalculatorQT->Calculate(text.toStdString()); //Вычислить
        while (text.endsWith('0') && text.size() != 1)
        {
            text.chop(1);
            if (text.endsWith("."))
            {
                text.chop(1);
                break;
            }
        }
        fontSize(text, displaystring, displayexp);
    }
    else text = "0";
    displaystring->setText(text); // вывести выражение
}