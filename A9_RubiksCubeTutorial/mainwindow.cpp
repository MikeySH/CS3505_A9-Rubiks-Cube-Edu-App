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
    connect(this, &MainWindow::rotateRight, &modelObj, &Model::rotateRight);
    connect(this, &MainWindow::rotateLeft, &modelObj, &Model::rotateLeft);
    connect(this, &MainWindow::rotateFlip, &modelObj, &Model::rotateFlip);


    //model to widget ------------
    connect(&modelObj, &Model::sendImage, ui->openGLWidget, &MainWidget::setNewImage);
    connect(&modelObj, &Model::resetCube, ui->openGLWidget, &MainWidget::resetCubePos);




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


    ui->perspective3DButton->click();
}

/*!
 * \brief MainWindow::keyPressEvent sends key events to 3d cube object to update drawing
 * \param event event defining key pressed
 */
void MainWindow::keyPressEvent(QKeyEvent *event){
    if( event->key() == Qt::Key_Right ){
        emit rotateRight();
    }
    else if( event->key() == Qt::Key_Left ){
        emit rotateLeft();
    }
    else if( event->key() == Qt::Key_Space ){
        emit rotateFlip();
    }
   ui->openGLWidget->keyPressEvent(event);
}



/*!
 * \brief MainWindow::~MainWindow destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/*!
 * \brief MainWindow::on_moveCubeLeft_clicked calls left key slot when move left button clicked
 */
void MainWindow::on_moveCubeLeft_clicked()
{
    QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Left, Qt::NoModifier);
    QCoreApplication::postEvent (this, event);
}

/*!
 * \brief MainWindow::on_moveCubeRight_clicked calls right key slot when move eight pressed
 */
void MainWindow::on_moveCubeRight_clicked()
{
    QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Right, Qt::NoModifier);
    QCoreApplication::postEvent (this, event);
\
}

/*!
 * \brief MainWindow::on_flipButton_clicked method defines what to call to flip rubix
 */
void MainWindow::on_flipButton_clicked()
{
    QKeyEvent *event = new QKeyEvent ( QEvent::KeyPress, Qt::Key_Space, Qt::NoModifier);
    QCoreApplication::postEvent (this, event);
}

void MainWindow::on_perspective2DButton_clicked()
{
    ui->frontLabel->show();
    ui->backLabel->show();
    ui->upLabel->show();
    ui->downLabel->show();
    ui->rightLabel->show();
    ui->leftLabel->show();

    ui->openGLWidget->hide();
    ui->moveCubeLeft->hide();
    ui->moveCubeRight->hide();
    ui->flipButton->hide();
}


void MainWindow::on_perspective3DButton_clicked()
{
    ui->frontLabel->hide();
    ui->backLabel->hide();
    ui->upLabel->hide();
    ui->downLabel->hide();
    ui->rightLabel->hide();
    ui->leftLabel->hide();

    ui->openGLWidget->show();
    ui->moveCubeLeft->show();
    ui->moveCubeRight->show();
    ui->flipButton->show();
    ui->openGLWidget->update();
}


