#include "mainwindow.h"
#include "ui_mainwindow.h"

#define IPGOBO "192.168.62.154"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mGobo.init(IPGOBO,16);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    mGobo.setValue(2,58);
    mGobo.sendFrame();
}

