#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include <QString>
#include <QRegularExpression>
#include <QProcess>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger= false;
bool addTrigger= false;
bool subTrigger= false;
bool sqrtTrigger = false;
bool sinTrigger = false;
bool cosTrigger = false;
bool powTrigger = false;
bool modTrigger = false;
bool factTrigger = false;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//        ui->te_result->setText("xxx");

        ui->te_result->setText(QString::number(calcVal));

        QPushButton *numButtons[10];
        for(int i=0; i<10; ++i){
            QString btnName = "btn"+QString::number(i);

            numButtons[i] = MainWindow::findChild<QPushButton *>(btnName);
            connect(numButtons[i],SIGNAL(released()),this,
                    SLOT(NumPressed())
                    );

        }

        // Connect signals and slots for math buttons
          connect(ui->btnPlus, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));
          connect(ui->btnMinus, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));
          connect(ui->btnMultiply, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));
          connect(ui->btnDivide, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));
          connect(ui->btnPow, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));
          connect(ui->btnSqrt, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));
          connect(ui->btnSin, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));
          connect(ui->btnCos, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));
          connect(ui->btnFactorial, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));


          connect(ui->btnMod, SIGNAL(released()), this,
                  SLOT(MathBtnPressed()));


        // Connect equals button
              connect(ui->btnResult, SIGNAL(released()), this,
                      SLOT(EqualButtonPressed()));

        // Connect change sign
        connect(ui->btnSignChange, SIGNAL(released()), this,
                      SLOT(changeNumSign()));


        // extra
//        connect(ui->btnDel, SIGNAL(released()), this,
//                      SLOT(deleteInput(1)));

}

MainWindow::~MainWindow()
{
    delete ui;



}

void MainWindow::EqualButtonPressed()
{
    qInfo() << "= pressed";

    double solution = 0.0;


    QString displayVal =ui->te_result->toPlainText();
    double dblDisplayVal = displayVal.toDouble();

    // Make sure a math button was pressed
    if (addTrigger || subTrigger || multTrigger || divTrigger ||
            powTrigger || sqrtTrigger || sinTrigger || cosTrigger || modTrigger || factTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        } else if (divTrigger) {
                    solution = calcVal / dblDisplayVal;
                } else if (powTrigger) {
                    solution = pow(calcVal, dblDisplayVal);
                } else if (sqrtTrigger) {
                    solution = sqrt(dblDisplayVal);
                } else if (sinTrigger) {
                    solution = sin(dblDisplayVal);
                } else if (cosTrigger) {
                    solution = cos(dblDisplayVal);
                } else if (modTrigger) {
                    solution = fmod(calcVal, dblDisplayVal);
                } else if (factTrigger) {
                    qInfo("silnia");
                if (dblDisplayVal < 0) {
                    // Error: cannot compute factorial of a negative number
                    ui->te_result->setText("Error");
                    return;
                } else {
                    // Calculate factorial using a loop
                    solution = 1;
                    for (int i = 1; i <= (int)dblDisplayVal; i++) {
                        solution *= i;
                    }
                }
            }
       }


    // Put solution in display
    ui->te_result->setText(QString::number(solution));
}

void MainWindow::NumPressed(){
    qInfo() << "Num btn pressed";

    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();
    QString displayVal = ui->te_result->toPlainText();
    if((displayVal.toDouble()==0)||(displayVal.toDouble()==0.0)){
        ui->te_result->setText(btnVal);

    }
    else{
        QString newVal = displayVal + btnVal;
        double numberNewVal = newVal.toDouble();
        ui->te_result->setText(QString::number(numberNewVal, 'g', 16));
    }



}

void MainWindow::MathBtnPressed()
{

    divTrigger = false;
    multTrigger= false;
    addTrigger= false;
    subTrigger= false;

    sqrtTrigger = false;
    sinTrigger = false;
    cosTrigger = false;
    powTrigger = false;
    modTrigger = false;
    factTrigger = false;


    QString displayVal = ui->te_result->toPlainText();
    calcVal = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString btnVal = button->text();

    if(QString::compare(btnVal, "/", Qt::CaseInsensitive) == 0){
          divTrigger = true;
      } else if(QString::compare(btnVal, "*", Qt::CaseInsensitive) == 0){
          multTrigger = true;
      } else if(QString::compare(btnVal, "+", Qt::CaseInsensitive) == 0){
          addTrigger = true;
        } else if (QString::compare(btnVal, "-", Qt::CaseInsensitive) == 0) {
            subTrigger = true;
        } else if (QString::compare(btnVal, "pow", Qt::CaseInsensitive) == 0) {
            powTrigger = true;
        } else if (QString::compare(btnVal, "sqrt", Qt::CaseInsensitive) == 0) {
            sqrtTrigger = true;
        } else if (QString::compare(btnVal, "sin", Qt::CaseInsensitive) == 0) {
            sinTrigger = true;
        } else if (QString::compare(btnVal, "cos", Qt::CaseInsensitive) == 0) {
            cosTrigger = true;
        } else if (QString::compare(btnVal, "mod", Qt::CaseInsensitive) == 0) {
            modTrigger = true;
        } else if (QString::compare(btnVal, "n!", Qt::CaseInsensitive) == 0) {
            factTrigger = true;
        }

        qInfo() << "Math btn pressed "<<btnVal;



    ui->te_result->setPlaceholderText(btnVal);//show last operation symbol
      ui->te_result->setText("");
}

void MainWindow::changeNumSign()
{


    QString displayVal = ui->te_result->toPlainText();

    QRegularExpression reg("[-+]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    bool hasMatch = match.hasMatch();


    if(hasMatch){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        // Put solution in display
        ui->te_result->setText(QString::number(dblDisplayValSign));
    }
}

//void deleteInput(int count)
//{
//    // 0 = all
//    // 1 = 1

//    qInfo() << "Dell "<<count;
//    qInfo() << "Dell ";


////    QString displayVal = ui->te_result->toPlainText();
////    calcVal = displayVal.toDouble();


//}






void MainWindow::on_btnDel_released()
{
    QString displayVal = ui->te_result->toPlainText();

    if (!displayVal.isEmpty()) {
        displayVal.remove(displayVal.length() - 1, 1);
        ui->te_result->setText(displayVal);
    }
}


void MainWindow::on_btnC_released()
{
    //clear
     ui->te_result->setText("");
}


void MainWindow::on_btnMysteryButton_released()
{

    qInfo() << "Mystery";

    QStringList args;
    args << "/c" << "start" << "https://youtu.be/dQw4w9WgXcQ";
    QProcess::startDetached("cmd.exe", args);
}

