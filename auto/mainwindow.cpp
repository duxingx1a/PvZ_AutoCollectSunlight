#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    label = new QLabel(this);
    QFont ft;
    label->setGeometry(QRect(150,60,200,80));
    label->setStyleSheet("color:#4D4DFF;");
    label->setText("程序未启动\n按z键启动");
    ft.setPointSize(14);
    label->setFont(ft);
    setFixedSize(400,200);

    startHook();
    currentThread = new OperationThread();
    currentThread->start();
    connect(KeyCapturer::instance(),&KeyCapturer::getKey,
            [=](int key)
            {
                qDebug()<<key<<"main-connect";
                if(key==90)
                    auto_operation();
                if(key==27)
                    exit(0);
            }
            );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::auto_operation()
{
    if(!isRuning)
    {
        currentThread->setRuning(!isRuning);
        label->setStyleSheet("color:#FF0000;");
        label->setText("程序运行中\n按z键暂停\n按ese退出");
    }
    else
    {
        currentThread->setRuning(!isRuning);
        label->setStyleSheet("color:#4D4DFF;");
        label->setText(" 程序已暂停\n按z键重新启动\n按ese退出");
    }
    isRuning = !isRuning;
    qDebug()<<isRuning;
}




