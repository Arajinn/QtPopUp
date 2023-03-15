#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "popupwidgetscontainer.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mPopUpWidgetsContainer=new PopUpWidgetsContainer(this);

    QObject::connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::onPopUpButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onPopUpButtonClicked()
{
    mPopUpWidgetsContainer->addPopUp(ui->textEdit->toPlainText());
}
