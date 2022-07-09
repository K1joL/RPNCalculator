#ifndef CLCLTR_H
#define CLCLTR_H

#include <QWidget>
#include <QStack>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <stack>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class Clcltr; }
QT_END_NAMESPACE

using namespace std;

class rpn
{
public:
    QString Calculate(string input)
    {
        string output = GetExpression(input);
        double result = Count(output);
        if (result == DBL_MAX || result == DBL_MIN )
        {
            if (result == DBL_MAX)
                return "Ошибка. Нельзя делить на ноль.";
            if (result == DBL_MIN)
                return "Ошибка. Некоректный ввод.";
        }
        return QString::number(result, 'f', 10);
    }
    string GetExpression(string input)
    {
        string output = "";
        stack<char> operStack;

        for (int i = 0; i < input.length(); i++)
        {
            //Разделители пропускаем
            if (isDelimeter(input[i]))
                continue;
            //Если число - считываем его полностью
            if (isdigit(input[i]))
            {
                //Пока не встретим разделитель или оператор добавляем число к строке вывода
                while (!isDelimeter(input[i]) && !isOperator(input[i]))
                {
                    output += input[i];
                    i++;

                    if (i == input.length()) break;
                }
                output += ' ';
                i--;
            }
            // Если оператор
            if (isOperator(input[i]))
            {
                //если символ ( добавляем в стек
                if (input[i] == '(')
                    operStack.push(input[i]);
                //если символ )
                else if (input[i] == ')')
                {
                    char s = operStack.top();
                    operStack.pop();

                    while (s != '(')
                    {
                        output += s; output += ' ';

                        s = operStack.top();
                        operStack.pop();
                    }
                }
                //если другой оператор
                else
                {
                    //если стек не пустой
                    if (operStack.size() > 0)
                    {
                        //Если приоритет символа <=
                        if (GetPriority(input[i]) <= GetPriority(operStack.top()))
                        {
                            output += operStack.top(); output += ' ';
                            operStack.pop();
                        }
                    }
                    operStack.push(input[i]);
                }
            }
        }
        while (operStack.size() > 0) {
            output += operStack.top(); output += " ";
            operStack.pop();
        }
        return output;
    }
    double Count(string input)
    {
        double result = 0.0;
        stack<double> temp;

        for (int i = 0; i < input.length(); i++)
        {
            if (isdigit(input[i]))
            {
                string a = "";
                while (!isDelimeter(input[i]) && !isOperator(input[i]))
                {
                    a += input[i];
                    i++;
                    if (i == input.length()) break;
                }
                temp.push(stod(a));
                i--;
            }
            else if (isOperator(input[i]))
            {
                double a = 0, b = 0;
                if (!temp.empty())
                {
                    a = temp.top();
                    temp.pop();
                }
                else { return DBL_MIN; }

                if (!temp.empty())
                {
                    b = temp.top();
                    temp.pop();
                }
                else if (input[i] == '-')
                {
                    b = 0;
                }
                else { return DBL_MIN; }

                switch (input[i])
                {
                case '+':
                    result = b + a;
                    break;
                case '-':
                    result = b - a;
                    break;
                case '*':
                    result = b * a;
                    break;
                case '/':
                    if (a)
                    {
                        result = b / a;
                        break;
                    }
                    else { return DBL_MAX; }
                case '%':
                    if (a)
                    {
                        result = (b - (trunc(b / a) * a));
                        break;
                    }
                    else { return DBL_MAX; }
                }
                temp.push(result);
            }
        }
        return temp.top();
    }
    bool isDelimeter(char c)
    {
        if (c == ' ' or c == '=')
            return true;

        return false;
    }
    bool isOperator(char c)
    {
        string oper = "+-*/%()";
        if (oper.find(c) != -1)
            return true;

        return false;
    }
    __int8 GetPriority(char c)
    {
        switch (c)
        {
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
        case '%': return 2;
        default: return 3;
        }
    }
};

class Clcltr : public QWidget
{
    Q_OBJECT

private:
    Ui::Clcltr *ui;
    QLabel *displaystring;
    QLabel *displayexp;
    QStack <QString> Stack;

public:
    Clcltr(QWidget *parent = nullptr);
    QPushButton* createButton (const QString& str);

public slots:
    void slotButtonClicked ();
    void slotBckspaceClicked();
};

#endif // CLCLTR_H