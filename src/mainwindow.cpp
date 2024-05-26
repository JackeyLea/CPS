#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QButtonGroup"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QButtonGroup btnGrp(ui->frameNav);
    for(int i=0;i<10;i++){
        QPushButton *btn=new QPushButton(ui->frameNav);
        btn->setText(QString("%1").arg(i+1));
        btn->setGeometry(10+(i%5)*35,10+(i/5)*35,25,25);
        btn->setStyleSheet(QString("border:1px solid gray;background-color:gray;"));
        btnGrp.addButton(btn);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
