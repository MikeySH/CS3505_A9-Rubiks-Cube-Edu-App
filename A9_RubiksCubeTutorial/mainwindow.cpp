#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

/*!
 * \brief MainWindow::MainWindow Method constructs MainWindow object and establishes
 * all connections needed
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

       ui->widget->show();
       ui->openGLWidget->show();

    // connection for sending grids to the faces
    connect(&modelObj, &Model::sendFrontGrid, ui->frontLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendBackGrid, ui->backLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendUpGrid, ui->upLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendDownGrid, ui->downLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendLeftGrid, ui->leftLabel, &QLabel::setPixmap);
    connect(&modelObj, &Model::sendRightGrid, ui->rightLabel, &QLabel::setPixmap);

    //View to model -----------------
    connect(ui->resetButton, &QPushButton::clicked, &modelObj, &Model::resetFaces);
    connect(ui->scrambleButton, &QPushButton::clicked, &modelObj, &Model::scramble);
    ui->resetButton->click();



    connect(this, &MainWindow::saveName, &modelObj, &Model::save);


    //Regular moves
    connect(ui->fButton, &QPushButton::clicked, &modelObj, &Model::frontMove);
    connect(ui->rButton, &QPushButton::clicked, &modelObj, &Model::rightMove);
    connect(ui->uButton, &QPushButton::clicked, &modelObj, &Model::upMove);
    connect(ui->bButton, &QPushButton::clicked, &modelObj, &Model::backMove);
    connect(ui->lButton, &QPushButton::clicked, &modelObj, &Model::leftMove);
    connect(ui->dButton, &QPushButton::clicked, &modelObj, &Model::downMove);

    //Prime moves
    connect(ui->fPrimeButton, &QPushButton::clicked, &modelObj, &Model::frontMovePrime);
    connect(ui->rPrimeButton, &QPushButton::clicked, &modelObj, &Model::rightMovePrime);
    connect(ui->uPrimeButton, &QPushButton::clicked, &modelObj, &Model::upMovePrime);
    connect(ui->bPrimeButton, &QPushButton::clicked, &modelObj, &Model::backMovePrime);
    connect(ui->lPrimeButton, &QPushButton::clicked, &modelObj, &Model::leftMovePrime);
    connect(ui->dPrimeButton, &QPushButton::clicked, &modelObj, &Model::downMovePrime);

}

/*!
 * \brief MainWindow::~MainWindow destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_pushButton_clicked()
{
    QString saveFile = QFileDialog::getSaveFileName(this, tr("Sprite Save As"), "", tr("PNG Files (*.png)"));
    if(!saveFile.isEmpty()){
        emit saveName(saveFile);
    }
}

