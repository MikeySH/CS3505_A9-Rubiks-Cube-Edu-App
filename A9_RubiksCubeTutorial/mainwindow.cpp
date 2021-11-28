#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget->show();

    // connection for sending grids to the faces
    connect(&modelObj, &Model::sendFrontGrid, ui->frontLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendBackGrid, ui->backLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendUpGrid, ui->upLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendDownGrid, ui->downLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendLeftGrid, ui->leftLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendRightGrid, ui->rightLabel, &QLabel::setPixmap);

    //View to model
    connect(ui->updateFaceButton, &QPushButton::clicked, &modelObj, &Model::updateFaces);

    connect(ui->fButton, &QPushButton::clicked, &modelObj, &Model::frontMove);
    connect(ui->rButton, &QPushButton::clicked, &modelObj, &Model::updateFaces);
    connect(ui->uButton, &QPushButton::clicked, &modelObj, &Model::updateFaces);
    connect(ui->bButton, &QPushButton::clicked, &modelObj, &Model::updateFaces);
    connect(ui->lButton, &QPushButton::clicked, &modelObj, &Model::updateFaces);
    connect(ui->dButton, &QPushButton::clicked, &modelObj, &Model::updateFaces);
}

MainWindow::~MainWindow()
{
    delete ui;
}




