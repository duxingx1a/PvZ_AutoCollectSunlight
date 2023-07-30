#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <OperationThread.h>
#include <QMainWindow>
#include <QLabel>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool isRuning;

private:
    Ui::MainWindow *ui;
    void auto_operation();

private:
    QLabel *label;
    OperationThread *currentThread = nullptr;
};
#endif // MAINWINDOW_H
