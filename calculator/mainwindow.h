#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void EqualButtonPressed();
    void NumPressed();
    void MathBtnPressed();
    void changeNumSign();

//    void deleteInput(int count);
//    void deleteInput(int);

    void on_btnDel_released();

    void on_btnC_released();

    void on_btnMysteryButton_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
