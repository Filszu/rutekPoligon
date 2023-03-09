#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionnew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(fileName);

    currentFile = fileName;
    qInfo()<<"OPENING FILE "<<fileName;
    if(!file.open(QIODevice::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot open file"+file.errorString());
        return;
    }
    setWindowTitle("Notepad# "+fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();


}


void MainWindow::on_actionsave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, "Save as");
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Cannot save as"+file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle("Notepad# "+fileName+"SAVED");
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;

    file.close();

}



void MainWindow::on_actionprint_triggered()
{
    QMessageBox::warning(this,"buy PREMIUM Notepad#😒","buy PREMIUM Notepad#😒\nOnly for 99$/month");
//    QPrinter printer;
//    printer.setPrinterName("printer name");
//    QPrintDialog pDialog(&printer, this);
//    if(pDialog.exec()==QDialog::Rejected){
//        QMessageBox::warning(this,"Warning","Cannot print it dude 😒");
//    }

//    ui->textEdit->print(&printer);

}


void MainWindow::on_actionexit_triggered()
{
   QApplication::quit();
}



void MainWindow::on_actionpaste_triggered()
{
     ui->textEdit->paste();
}


void MainWindow::on_actioncopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();
}

