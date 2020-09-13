/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include <cmath>

#include "button.h"
#include "calculator.h"

//! [0]
Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    sumInMemory = 0.0;
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    waitingForOperand = true;
    pi=3.1415926;

//! [0]

//! [1]
    display = new QLineEdit("0");
//! [1] //! [2]
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setMaxLength(20);

    QFont font = display->font();
    font.setPointSize(font.pointSize() + 8);
    display->setFont(font);
//! [2]

//! [4]
    for (int i = 0; i < 10; ++i) {
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));
    }
    digitButtons[10]=createButton(tr("a"),SLOT(digitClicked()));
    digitButtons[11]=createButton(tr("b"),SLOT(digitClicked()));
    digitButtons[12]=createButton(tr("c"),SLOT(digitClicked()));
    digitButtons[13]=createButton(tr("d"),SLOT(digitClicked()));
    digitButtons[14]=createButton(tr("e"),SLOT(digitClicked()));
    digitButtons[15]=createButton(tr("f"),SLOT(digitClicked()));
    Button *pointButton = createButton(tr("."), SLOT(pointClicked()));
    Button *changeSignButton = createButton(tr("\302\261"), SLOT(changeSignClicked()));

    Button *backspaceButton = createButton(tr("Backspace"), SLOT(backspaceClicked()));
    //Button *clearButton = createButton(tr("Clear"), SLOT(clear()));
    Button *clearAllButton = createButton(tr("Clear All"), SLOT(clearAll()));
    Button *left=createButton(tr("("),SLOT(leftclicked()));
    Button *right=createButton(tr(")"),SLOT(rightclicked()));
    Button *sin=createButton(tr("sin"),SLOT(sinclicked()));
    Button *cos=createButton(tr("cos"),SLOT(cosclicked()));
    Button *lg=createButton(tr("lg"),SLOT(lgclicked()));
    Button *cmp=createButton(tr("cmp"),SLOT(cmpclicked()));
    Button *gcd=createButton(tr("gcd"),SLOT(gcdclicked()));
    Button *lcm=createButton(tr("lcm"),SLOT(lcmclicked()));
    Button *bin= createButton(tr("(2)"),SLOT(jinzhiclicked()));
    Button *hex= createButton(tr("(16)"),SLOT(jinzhiclicked()));
    Button *binn=createButton(tr("[2]"),SLOT(binclicked()));
    Button *hexx=createButton(tr("[16]"),SLOT(hexclicked()));


    Button *divisionButton = createButton(tr("\303\267"), SLOT(multiplicativeOperatorClicked()));
    Button *timesButton = createButton(tr("\303\227"), SLOT(multiplicativeOperatorClicked()));
    Button *minusButton = createButton(tr("-"), SLOT(additiveOperatorClicked()));
    Button *plusButton = createButton(tr("+"), SLOT(additiveOperatorClicked()));

    Button *squareRootButton = createButton(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    Button *powerButton = createButton(tr("x\302\262"), SLOT(unaryOperatorClicked()));
    Button *reciprocalButton = createButton(tr("1/x"), SLOT(unaryOperatorClicked()));
    //Button *bin= createButton(tr("(2)"),SLOT(unaryOperatorClicked()));
    //Button *hex= createButton(tr("(16)"),SLOT(unaryOperatorClicked()));
    Button *equalButton = createButton(tr("="), SLOT(equalClicked()));

//! [4]

//! [5]
    QGridLayout *mainLayout = new QGridLayout;
//! [5] //! [6]
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(display, 0, 0, 1, 9);
    mainLayout->addWidget(backspaceButton, 1, 0, 1, 2);
    //mainLayout->addWidget(clearButton, 1, 2, 1, 2);
    mainLayout->addWidget(clearAllButton, 1, 2, 1, 3);




    for (int i = 1; i < 10; ++i) {
        int row = ((9 - i) / 3) + 2;
        int column = ((i - 1) % 3) ;
        mainLayout->addWidget(digitButtons[i], row, column);
    }

    mainLayout->addWidget(digitButtons[0], 5, 1);
    mainLayout->addWidget(digitButtons[10],3,7);
    mainLayout->addWidget(digitButtons[11],4,7);
    mainLayout->addWidget(digitButtons[12],5,7);
    mainLayout->addWidget(digitButtons[13],3,8);
    mainLayout->addWidget(digitButtons[14],4,8);
    mainLayout->addWidget(digitButtons[15],5,8);
    mainLayout->addWidget(pointButton, 5, 2);
    mainLayout->addWidget(changeSignButton, 5, 0);
    mainLayout->addWidget(left,2,3);
    mainLayout->addWidget(right,3,3);
    mainLayout->addWidget(sin,4,3);
    mainLayout->addWidget(cos,5,3);
    mainLayout->addWidget(lg,2,6);
    mainLayout->addWidget(cmp,3,6);
    mainLayout->addWidget(gcd,4,6);
    mainLayout->addWidget(lcm,5,6);
    mainLayout->addWidget(bin,1,5);
    mainLayout->addWidget(hex,1,6);
    mainLayout->addWidget(binn,1,7,1,2);
    mainLayout->addWidget(hexx,2,7,1,2);

    mainLayout->addWidget(divisionButton, 2, 4);
    mainLayout->addWidget(timesButton, 3, 4);
    mainLayout->addWidget(minusButton, 4, 4);
    mainLayout->addWidget(plusButton, 5, 4);

    mainLayout->addWidget(squareRootButton, 2, 5);
    mainLayout->addWidget(powerButton, 3, 5);
    mainLayout->addWidget(reciprocalButton, 4, 5);
    mainLayout->addWidget(equalButton, 5, 5);
    setLayout(mainLayout);

    setWindowTitle(tr("计算器"));
}
//! [6]

//! [7]
void Calculator::digitClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    int digitValue;
    if(clickedButton->text()=="a")digitValue=10;
    else if(clickedButton->text()=="b")digitValue=11;
    else if(clickedButton->text()=="c")digitValue=12;
    else if(clickedButton->text()=="d")digitValue=13;
    else if(clickedButton->text()=="e")digitValue=14;
    else if(clickedButton->text()=="f")digitValue=15;
    else digitValue = clickedButton->text().toInt();
    if (display->text() == "0" && digitValue == 0.0)
        return;

    if (waitingForOperand) {
        display->clear();
        waitingForOperand = false;
    }
    if(digitValue==10)
        display->setText(display->text() + "a");
    else if(digitValue==11)
        display->setText(display->text() + "b");
    else if(digitValue==12)
        display->setText(display->text() + "c");
    else if(digitValue==13)
        display->setText(display->text() + "d");
    else if(digitValue==14)
        display->setText(display->text() + "e");
    else if(digitValue==15)
        display->setText(display->text() + "f");
    else
    display->setText(display->text() + QString::number(digitValue));
}
//! [7]

//! [8]
void Calculator::unaryOperatorClicked()
//! [8] //! [9]
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();
    double result = 0.0;

    if (clickedOperator == tr("Sqrt")) {
        if (operand < 0.0) {
            abortOperation();
            return;
        }
        result = std::sqrt(operand);
    } else if (clickedOperator == tr("x\302\262")) {
        result = std::pow(operand, 2.0);
    } else if (clickedOperator == tr("1/x")) {
        if (operand == 0.0) {
            abortOperation();
            return;
        }
        result = 1.0 / operand;
    }
    display->setText(QString::number(result));
    waitingForOperand = true;
}
//! [9]

//! [10]
void Calculator::additiveOperatorClicked()
//! [10] //! [11]
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

//! [11] //! [12]
    if (!pendingMultiplicativeOperator.isEmpty()) {
//! [12] //! [13]
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }

//! [13] //! [14]
    if (!pendingAdditiveOperator.isEmpty()) {
//! [14] //! [15]
        if (!calculate(operand, pendingAdditiveOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(sumSoFar));
    } else {
        sumSoFar = operand;
    }

//! [15] //! [16]
    pendingAdditiveOperator = clickedOperator;
//! [16] //! [17]
    waitingForOperand = true;
}
//! [17]
//! [18]
void Calculator::multiplicativeOperatorClicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty()) {
        if (!calculate(operand, pendingMultiplicativeOperator)) {
            abortOperation();
            return;
        }
        display->setText(QString::number(factorSoFar));
    } else {
        factorSoFar = operand;
    }

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}
//! [18]

//! [20]
void Calculator::equalClicked()
{
   double operand=display->text().toDouble();

    if (!pendingMultiplicativeOperator.isEmpty())
    {
        if (!calculate(operand, pendingMultiplicativeOperator))
        {
            abortOperation();
            return;
        }
        operand = factorSoFar;
        factorSoFar = 0.0;
        pendingMultiplicativeOperator.clear();
    }
    if (!pendingAdditiveOperator.isEmpty())
    {
        if (!calculate(operand, pendingAdditiveOperator))
        {
            abortOperation();
            return;
        }
        pendingAdditiveOperator.clear();
    }
    else
    {
        sumSoFar = operand;
    }

    display->setText(QString::number(sumSoFar));
    sumSoFar = 0.0;
    waitingForOperand = true;
}
//! [20]

//! [22]
void Calculator::pointClicked()
{
    if (waitingForOperand)
        display->setText("0");
    if (!display->text().contains('.'))
        display->setText(display->text() + tr("."));
    waitingForOperand = false;
}
void Calculator::sinclicked()
{
    QString text = display->text();
    double value=text.toDouble();
        double sumSoFar=std::sin(value*pi/180);
    display->setText(QString::number(sumSoFar));

}
void Calculator::cosclicked()
{
    QString text = display->text();
    double value=text.toDouble();
        double sumSoFar=std::cos(value*pi/180);
    display->setText(QString::number(sumSoFar));
}
void Calculator::lgclicked()
{
    QString text = display->text();
    double value=text.toDouble();
        double sumSoFar=std::log10(value);
    display->setText(QString::number(sumSoFar));
}
//! [22]
void Calculator::binclicked()
{
    QString text = display->text();
    int value=text.toInt();
        double temp=0.0;
        for(int i=0;i<8;i++)
        {
        temp=value%10*(std::pow(2,i))+temp;
        value=value/10;
        }
    display->setText(QString::number(temp));
}
void Calculator::hexclicked()
{

     QString text = display->text();

     if (text=="1a")
             display->setText(QString::number(26));
       else if (text=="1b")
                 display->setText(QString::number(27));
         else   if (text=="1c")
                 display->setText(QString::number(28));
     else   if (text=="1d")
             display->setText(QString::number(29));
     else   if (text=="1e")
             display->setText(QString::number(30));
     else   if (text=="1f")
             display->setText(QString::number(31));
     else   if (text=="2a")
             display->setText(QString::number(42));
     else   if (text=="2b")
             display->setText(QString::number(43));
     else   if (text=="2c")
             display->setText(QString::number(44));
     else   if (text=="2d")
             display->setText(QString::number(45));
     else   if (text=="2e")
             display->setText(QString::number(46));
     else   if (text=="2f")
             display->setText(QString::number(47));
     else   if (text=="3a")
             display->setText(QString::number(58));
     else   if (text=="3b")
             display->setText(QString::number(59));
     else   if (text=="3c")
             display->setText(QString::number(60));
     else   if (text=="3d")
             display->setText(QString::number(61));
     else   if (text=="3e")
             display->setText(QString::number(62));
     else   if (text=="3f")
             display->setText(QString::number(63));
     else   if (text=="4a")
             display->setText(QString::number(74));
     else   if (text=="4b")
             display->setText(QString::number(75));
     else   if (text=="4c")
             display->setText(QString::number(76));
     else   if (text=="4d")
             display->setText(QString::number(77));
     else   if (text=="4e")
             display->setText(QString::number(78));
     else   if (text=="4f")
             display->setText(QString::number(79));
     else   if (text=="5a")
             display->setText(QString::number(90));
     else   if (text=="5b")
             display->setText(QString::number(91));
     else   if (text=="5c")
             display->setText(QString::number(92));
     else   if (text=="5d")
             display->setText(QString::number(93));
     else   if (text=="5e")
             display->setText(QString::number(94));
     else   if (text=="5f")
             display->setText(QString::number(95));
     else   if (text=="6a")
             display->setText(QString::number(106));
     else   if (text=="6b")
             display->setText(QString::number(107));
     else   if (text=="6c")
             display->setText(QString::number(108));
     else   if (text=="6d")
             display->setText(QString::number(109));
     else   if (text=="6e")
             display->setText(QString::number(110));
     else   if (text=="6f")
             display->setText(QString::number(111));
     else   if (text=="7a")
             display->setText(QString::number(122));
     else   if (text=="7b")
             display->setText(QString::number(123));
     else   if (text=="7c")
             display->setText(QString::number(124));
     else   if (text=="7d")
             display->setText(QString::number(125));
     else   if (text=="7e")
             display->setText(QString::number(126));
     else   if (text=="7f")
             display->setText(QString::number(127));
     else   if (text=="8a")
             display->setText(QString::number(138));
     else   if (text=="8b")
             display->setText(QString::number(139));
     else   if (text=="8c")
             display->setText(QString::number(140));
     else   if (text=="8d")
             display->setText(QString::number(141));
     else   if (text=="8e")
             display->setText(QString::number(142));
     else   if (text=="8f")
             display->setText(QString::number(143));
     else   if (text=="9a")
             display->setText(QString::number(154));
     else   if (text=="9b")
             display->setText(QString::number(155));
     else   if (text=="9c")
             display->setText(QString::number(156));
     else   if (text=="9d")
             display->setText(QString::number(157));
     else   if (text=="9e")
             display->setText(QString::number(158));
     else   if (text=="9f")
             display->setText(QString::number(159));
     else   if (text=="aa")
             display->setText(QString::number(170));
     else   if (text=="ab")
             display->setText(QString::number(171));
     else   if (text=="ac")
             display->setText(QString::number(172));
     else   if (text=="ad")
             display->setText(QString::number(173));
     else   if (text=="ae")
             display->setText(QString::number(174));
     else   if (text=="af")
             display->setText(QString::number(175));
     else   if (text=="ba")
             display->setText(QString::number(186));
     else   if (text=="bb")
             display->setText(QString::number(187));
     else   if (text=="bc")
             display->setText(QString::number(188));
     else   if (text=="bd")
             display->setText(QString::number(189));
     else   if (text=="be")
             display->setText(QString::number(190));
     else   if (text=="bf")
             display->setText(QString::number(191));
     else   if (text=="ca")
             display->setText(QString::number(202));
     else   if (text=="cb")
             display->setText(QString::number(203));
     else   if (text=="cc")
             display->setText(QString::number(204));
     else   if (text=="cd")
             display->setText(QString::number(205));
     else   if (text=="ce")
             display->setText(QString::number(206));
     else   if (text=="cf")
             display->setText(QString::number(207));
     else   if (text=="da")
             display->setText(QString::number(218));
     else   if (text=="db")
             display->setText(QString::number(219));
     else   if (text=="dc")
             display->setText(QString::number(220));
     else   if (text=="db")
             display->setText(QString::number(221));
     else   if (text=="de")
             display->setText(QString::number(222));
     else   if (text=="df")
             display->setText(QString::number(223));
     else   if (text=="ea")
             display->setText(QString::number(234));
     else   if (text=="eb")
             display->setText(QString::number(235));
     else   if (text=="ec")
             display->setText(QString::number(236));
     else   if (text=="ed")
             display->setText(QString::number(237));
     else   if (text=="ee")
             display->setText(QString::number(238));
     else   if (text=="ef")
             display->setText(QString::number(239));
     else   if (text=="fa")
             display->setText(QString::number(250));
     else   if (text=="fb")
             display->setText(QString::number(251));
     else   if (text=="fc")
             display->setText(QString::number(252));
     else   if (text=="fd")
             display->setText(QString::number(253));
     else   if (text=="fe")
             display->setText(QString::number(254));
     else   if (text=="ff")
             display->setText(QString::number(255));
     else   if (text=="a1")
             display->setText(QString::number(161));
     else   if (text=="a2")
             display->setText(QString::number(162));
     else   if (text=="a3")
             display->setText(QString::number(163));
     else   if (text=="a4")
             display->setText(QString::number(164));
     else   if (text=="a5")
             display->setText(QString::number(165));
     else   if (text=="a6")
             display->setText(QString::number(166));
     else   if (text=="a7")
             display->setText(QString::number(167));
     else   if (text=="a8")
             display->setText(QString::number(168));
     else   if (text=="a9")
             display->setText(QString::number(169));
     else   if (text=="b1")
             display->setText(QString::number(177));
     else   if (text=="b2")
             display->setText(QString::number(178));
     else   if (text=="b3")
             display->setText(QString::number(179));
     else   if (text=="b4")
             display->setText(QString::number(180));
     else   if (text=="b5")
             display->setText(QString::number(181));
     else   if (text=="b6")
             display->setText(QString::number(182));
     else   if (text=="b7")
             display->setText(QString::number(183));
     else   if (text=="b8")
             display->setText(QString::number(184));
     else   if (text=="b9")
             display->setText(QString::number(185));
     else   if (text=="c1")
             display->setText(QString::number(193));
     else   if (text=="c2")
             display->setText(QString::number(194));
     else   if (text=="c3")
             display->setText(QString::number(195));
     else   if (text=="c4")
             display->setText(QString::number(196));
     else   if (text=="c5")
             display->setText(QString::number(197));
     else   if (text=="c6")
             display->setText(QString::number(198));
     else   if (text=="c7")
             display->setText(QString::number(199));
     else   if (text=="c8")
             display->setText(QString::number(200));
     else   if (text=="c9")
             display->setText(QString::number(201));
     else   if (text=="d1")
             display->setText(QString::number(209));
     else   if (text=="d2")
             display->setText(QString::number(210));
     else   if (text=="d3")
             display->setText(QString::number(211));
     else   if (text=="d4")
             display->setText(QString::number(212));
     else   if (text=="d5")
             display->setText(QString::number(213));
     else   if (text=="d6")
             display->setText(QString::number(214));
     else   if (text=="d7")
             display->setText(QString::number(215));
     else   if (text=="d8")
             display->setText(QString::number(216));
     else   if (text=="d9")
             display->setText(QString::number(217));
     else   if (text=="e1")
             display->setText(QString::number(225));
     else   if (text=="e2")
             display->setText(QString::number(226));
     else   if (text=="e3")
             display->setText(QString::number(227));
     else   if (text=="e4")
             display->setText(QString::number(228));
     else   if (text=="e5")
             display->setText(QString::number(229));
     else   if (text=="e6")
             display->setText(QString::number(230));
     else   if (text=="e7")
             display->setText(QString::number(231));
     else   if (text=="e8")
             display->setText(QString::number(232));
     else   if (text=="e9")
             display->setText(QString::number(233));
     else   if (text=="f1")
             display->setText(QString::number(241));
     else   if (text=="f2")
             display->setText(QString::number(242));
     else   if (text=="f3")
             display->setText(QString::number(243));
     else   if (text=="f4")
             display->setText(QString::number(244));
     else   if (text=="f5")
             display->setText(QString::number(245));
     else   if (text=="f6")
             display->setText(QString::number(246));
     else   if (text=="f7")
             display->setText(QString::number(247));
     else   if (text=="f8")
             display->setText(QString::number(248));
     else   if (text=="f9")
             display->setText(QString::number(249));
    else
     {
         int value=text.toInt();
         double temp=0.0;
         for(int i=0;i<2;i++)
         {
         temp=value%10*(std::pow(16,i))+temp;
         value=value/10;
         }
    display->setText(QString::number(temp));
     }
}
//! [24]
void Calculator::changeSignClicked()
{
    QString text = display->text();
    double value = text.toDouble();

    if (value > 0.0) {
        text.prepend(tr("-"));
    } else if (value < 0.0) {
        text.remove(0, 1);
    }
    display->setText(text);
}

//! [24]

//! [26]
void Calculator::backspaceClicked()
{
    if (waitingForOperand)
        return;

    QString text = display->text();
    text.chop(1);
    if (text.isEmpty()) {
        text = "0";
        waitingForOperand = true;
    }
    display->setText(text);
}
//! [26]

//! [28]
//! [28]

//! [30]
//!

void Calculator::leftclicked()
{
    display->setText("没实现");
}
void Calculator::rightclicked()
{
    display->setText("没实现");
}


void Calculator::cmpclicked()
{
        Button *clickedButton = qobject_cast<Button *>(sender());
        QString clickedOperator = clickedButton->text();
        double operand = display->text().toDouble();

        calculate(operand,"cmp");
            display->setText(QString::number(factorSoFar));

        pendingMultiplicativeOperator = clickedOperator;
        waitingForOperand = true;

}

void Calculator::lcmclicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    calculate(operand,"lcm");
        display->setText(QString::number(factorSoFar));

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}
void Calculator::gcdclicked()
{
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    double operand = display->text().toDouble();

    calculate(operand,"gcd");
        display->setText(QString::number(factorSoFar));

    pendingMultiplicativeOperator = clickedOperator;
    waitingForOperand = true;
}
void Calculator::jinzhiclicked()
{

    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();
    int operand = display->text().toInt();
    int result=0;
    int bin[8];//hex[2];
    //QString *hexx;
    int i=7;
    if (clickedOperator == tr("(2)")) {
            while(i>=0)
            {
                if(operand%2)
                {bin[i--]=1;
                operand=operand/2;}
                else
                   { bin[i--]=0;
            operand=operand/2;}
            }
       result=bin[7]+bin[6]*10+bin[5]*100+bin[4]*1000+bin[3]*10000+bin[2]*100000+bin[1]*1000000+bin[0]*10000000;
       display->setText(QString::number(result));
}
    else if(clickedOperator == tr("(16)"))
    {
        QString text;
        int rem=operand%16;
        if(rem<10)
           text=(QString::number(rem));
        else if(rem==10)
            text="a";
        else if(rem==11)
            text="b";
        else if(rem==12)
            text="c";
        else if(rem==13)
            text="d";
        else if(rem==14)
            text="e";
        else if(rem==15)
            text="f";
        else
            text="####";

        operand/=16;
        if(operand<10)
            text.prepend(QString::number(operand));
        else if(rem==10)
            text.prepend("a");
        else if(rem==11)
            text.prepend("b");
        else if(rem==12)
             text.prepend("c");
        else if(rem==13)
            text.prepend("d");
        else if(rem==14)
            text.prepend("e");
        else if(rem==15)
            text.prepend("f");
        else
            text.prepend("####");
        display->setText(text);
    }
}

void Calculator::clearAll()
{
    sumSoFar = 0.0;
    factorSoFar = 0.0;
    pendingAdditiveOperator.clear();
    pendingMultiplicativeOperator.clear();
    display->setText("0");
    waitingForOperand = true;
}
//! [30]

//! [32]
Button *Calculator::createButton(const QString &text, const char *member)
{
    Button *button = new Button(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}
//! [34]

//! [36]
void Calculator::abortOperation()
{
    clearAll();
    display->setText(tr("####"));
}
//! [36]

//! [38]
bool Calculator::calculate(double rightOperand, const QString &pendingOperator)
{
    if (pendingOperator == tr("+")) {
        sumSoFar += rightOperand;
    } else if (pendingOperator == tr("-")) {
        sumSoFar -= rightOperand;
    } else if (pendingOperator == tr("\303\227")) {
        factorSoFar *= rightOperand;
    } else if (pendingOperator == tr("\303\267")) {
        if (rightOperand == 0.0)
            return false;
        factorSoFar /= rightOperand;
    }
    else if(pendingOperator=="cmp"){
        if(factorSoFar>rightOperand)
            factorSoFar=factorSoFar;
        else
            factorSoFar=rightOperand;
    }
    else if(pendingOperator=="gcd"){
        double i=rightOperand;
        while(i)
        {

            if((fmod(factorSoFar,i)==0)&&(fmod(rightOperand,i)==0))
            {factorSoFar=i;break;}
            else
                i--;
        }
    }
    else if(pendingOperator=="lcm"){
        double i=rightOperand;
        while(i<=factorSoFar*rightOperand)
        {
            if((fmod(i,factorSoFar)==0)&&(fmod(i,rightOperand)==0))
            {factorSoFar=i;break;}
            else
                i++;
        }
        factorSoFar=i;
    }
    return true;
}
//! [38]
