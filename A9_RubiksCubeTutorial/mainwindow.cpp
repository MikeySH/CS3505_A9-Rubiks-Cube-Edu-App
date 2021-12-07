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

    ui->lastButtonStep->hide();
    ui->nextStepButton->hide();

    hideAllStepLabels();


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
    connect(ui->learnButton, &QPushButton::clicked, &modelObj, &Model::startTutorial);
    connect(ui->lastButtonStep, &QPushButton::clicked, &modelObj, &Model::decrementStep);
    connect(ui->nextStepButton, &QPushButton::clicked, &modelObj, &Model::incrementStep);
    connect(ui->stepComboBox, &QComboBox::activated, &modelObj, &Model::setStep);

    // view to view
    connect(ui->stepComboBox, &QComboBox::activated, this, &MainWindow::on_learnButton_clicked);

    // model to View
    connect(&modelObj, &Model::sendStep, this, &MainWindow::showCurrentStep);


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

/*!
 * \brief MainWindow::showCurrentStep draws whatever step is requested by model
 * \param stepIndex the ith step we are on
 */
void MainWindow::showCurrentStep(int stepIndex){

    ui->stepComboBox->setCurrentIndex(stepIndex);

    switch (stepIndex){
    case 0:

        // white cross
        drawWhiteCrossStep();
        break;
    case 1:

        // white corners
        drawWhiteCornersStep();
        break;
    case 2:

        // 2nd layer
        drawSecondLayerStep();
        break;
    case 3:

        // yellow cross
        drawYellowCrossStep();
        break;
    case 4:

        // yellow corners
        drawYellowCornerStep();
        break;
    case 5:

        // 3rd layer
        drawThirdLayerStep();
        break;
    }

}

/*!
 * \brief MainWindow::drawCase0 method draws the correct labels, etc when model tells view it is on step 1 of learning
 */
void MainWindow::drawWhiteCrossStep(){
    ui->lastButtonStep->setEnabled(false);
    ui->nextStepButton->setEnabled(true);

    showAllStepLables();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/White Cross/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/White Cross/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/White Cross/3.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/White Cross/4.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase1 method draws the correct labels, etc when model tells view it is on step 2 of learning
 */
void MainWindow::drawWhiteCornersStep(){
    showAllStepLables();
    enableLastAndNextStepButtons();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/White Corners/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/White Corners/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/White Corners/3.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/White Corners/4.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase2 method draws the correct labels, etc when model tells view it is on step 2 of learning
 */
void MainWindow::drawSecondLayerStep(){
    enableLastAndNextStepButtons();
    showAllStepLables();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/Second Layer/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/Second Layer/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/Second Layer/3.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/Second Layer/4.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase3 method draws the correct labels, etc when model tells view it is on step 4 of learning
 */
void MainWindow::drawYellowCrossStep(){
    enableLastAndNextStepButtons();
    showAllStepLables();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/Yellow Cross/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/Yellow Cross/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/Yellow Cross/3.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/Yellow Cross/4.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase4 method draws the correct labels, etc when model tells view it is on step 5 of learning
 */
void MainWindow::drawYellowCornerStep(){
    enableLastAndNextStepButtons();
    ui->img1Label->show();
    ui->img2Label->hide();
    ui->img3Label->hide();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->hide();
    ui->step3Label->hide();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/Yellow Corners/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/Yellow Corners/2.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase5 method draws the correct labels, etc when model tells view it is on step 6 of learning
 */
void MainWindow::drawThirdLayerStep(){
    ui->lastButtonStep->setEnabled(true);
    ui->nextStepButton->setEnabled(false);


    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->hide();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->hide();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/Third Layer/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/Third Layer/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/Third Layer/3.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::showAllStepLables method draws labels that shows "step 1", "step 2", "step 3"
 */
void MainWindow::showAllStepLables(){
    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();
}

/*!
 * \brief MainWindow::hideAllStepLabels method hides all step labels that show "step 1", "step 2", "step 3"
 */
void MainWindow::hideAllStepLabels(){
    ui->step1Label->hide();
    ui->step2Label->hide();
    ui->step3Label->hide();
    ui->hintLabel->hide();
}

/*!
 * \brief MainWindow::on_learnButton_clicked show all buttons related to steps when clicked
 */
void MainWindow::on_learnButton_clicked()
{
    ui->lastButtonStep->show();
    ui->nextStepButton->show();
}

/*!
 * \brief MainWindow::enableLastAndNextStepButtons enables both next step and previous step buttons
 */
void MainWindow::enableLastAndNextStepButtons(){
    ui->lastButtonStep->setEnabled(true);
    ui->nextStepButton->setEnabled(true);
}

