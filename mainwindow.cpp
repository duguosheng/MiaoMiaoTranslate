#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tsWidget = new TranslateWidget(this);
    setCentralWidget(tsWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
