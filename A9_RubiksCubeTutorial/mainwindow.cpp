#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
// https://www.google.com/search?q=rubiks+3d+png&tbm=isch&ved=2ahUKEwj9sKiMmNb0AhW1oK0KHU_vDbsQ2-cCegQIABAA&oq=rubiks+3d+png&gs_lcp=CgNpbWcQAzoHCCMQ7wMQJ1CEBViICGCVCWgAcAB4AIABWogB8wGSAQEzmAEAoAEBqgELZ3dzLXdpei1pbWfAAQE&sclient=img&ei=U6-xYb27N7XBtgXP3rfYCw&bih=645&biw=720#imgrc=9wGCuLAgjG9I9M
// https://toppng.com/free-image/free-right-arrow-symbol-png-vector-arrow-right-vector-PNG-free-PNG-Images_220282
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

    ui->widget->hide();
    ui->openGLWidget->show();
    ui->celebrationWidget->hide();

    ui->lastButtonStep->hide();
    ui->nextStepButton->hide();

    ui->hintLabel->setStyleSheet("border-image: url(:/bubble.png);");

    hideAllLearningUI();

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
    connect(ui->restartButton, &QPushButton::clicked, ui->celebrationWidget, &QWidget::hide);

    // model to View
    connect(&modelObj, &Model::sendStep, this, &MainWindow::showCurrentStep);
    connect(&modelObj, &Model::showAnimation, ui->celebrationWidget, &QWidget::show);
    connect(&modelObj, &Model::showAnimation, ui->celebrationWidget, &celebrationBox2D::startWorld);
    connect(&modelObj, &Model::showAnimation, this, &MainWindow::hideAllLearningUI);
    connect(&modelObj, &Model::sendCurrentTime, ui->currentTimeLabel, &QLabel::setText);

    //model to widget ------------
    connect(&modelObj, &Model::sendImage, ui->openGLWidget, &Cube3DWidget::setNewImage);
    connect(&modelObj, &Model::resetCube, ui->openGLWidget, &Cube3DWidget::resetCubePos);


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

    //have buttons have hover feature
    ui->fButton->installEventFilter(this);
    ui->rButton->installEventFilter(this);
    ui->uButton->installEventFilter(this);
    ui->bButton->installEventFilter(this);
    ui->lButton->installEventFilter(this);
    ui->dButton->installEventFilter(this);
    ui->fPrimeButton->installEventFilter(this);
    ui->rPrimeButton->installEventFilter(this);
    ui->uPrimeButton->installEventFilter(this);
    ui->bPrimeButton->installEventFilter(this);
    ui->lPrimeButton->installEventFilter(this);
    ui->dPrimeButton->installEventFilter(this);

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
        //teach about edge and corners and center pieces
        drawCubePiecesStep();
        break;
    case 1:
        drawButtonMovesStep();
        //button moves and view selection
        break;
    case 2:

        // white cross
        drawWhiteCrossStep();
        break;
    case 3:
        // white corners
        drawWhiteCornersStep();
        break;
    case 4:

        // 2nd layer
        drawSecondLayerStep();
        break;
    case 5:

        // yellow cross
        drawYellowCrossStep();
        break;
    case 6:

        // yellow corners
        drawYellowCornerStep();
        break;
    case 7:

        // 3rd layer
        drawThirdLayerStep();
        break;
    }

}

void MainWindow::drawCubePiecesStep(){
    ui->lastButtonStep->setEnabled(false);
    ui->nextStepButton->setEnabled(true);
    hideAllLearningUI();
    ui->stepComboBox->show();
    showStepButtons();

    ui->case1Label->show();
    ui->case2Label->show();
    ui->case3Label->show();
    ui->case1Label->setText("Edge");
    ui->case2Label->setText("Corner");
    ui->case3Label->setText("Center");


    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/preface/edge.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/preface/corner.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/preface/center.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->hintLabel->show();
    ui->hintTextLabel->show();
    ui->hintTextLabel->setText("Edge: Pieces with two colors. There are twelve edge pieces located in the middle row. \n"
                               "Coner: Pieces with three colors. There are eight corner pieces located on the corners. \n"
                               "Center: Pieces with once color. There are six center pieces located in the center of each side, center pieces DO NOT MOVE and represent the color of their side/face. \n"
                               "Center colors are always opposite each other: \n"
                               "White is opposite yellow \n"
                               "Orange is opposite red \n"
                               "Green is opposite blue");
}

void MainWindow::drawButtonMovesStep(){
    ui->lastButtonStep->setEnabled(true);
    hideAllLearningUI();
    showStepButtons();
    ui->stepComboBox->show();
    ui->notationLabel->show();


    ui->notationLabel->setPixmap(QPixmap::fromImage(QImage(":/preface/cubingNotations.png").scaled(ui->notationLabel->width(), ui->notationLabel->height(), Qt::KeepAspectRatio)));

    ui->hintLabel->show();
    ui->hintTextLabel->show();
    ui->hintTextLabel->setText("Each face of the cube is represented by a letter. Moves are done in a clockwise rotation. "
                               "Letters with a ' are pronounced as \"LETTER prime\" and will have a counter-clockwise rotation. "
                               "An move that starts with a letter and end with a 2 such as \"F2\" for example would mean to turn that face twice.");

}

/*!
 * \brief MainWindow::drawCase0 method draws the correct labels, etc when model tells view it is on step 1 of learning
 */
void MainWindow::drawWhiteCrossStep(){

    hideAllLearningUI();
    showStepButtons();
    showAllStepLables();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();
    ui->hintLabel->show();
    ui->hintTextLabel->show();

    ui->case1Label->show();
    ui->case3Label->show();
    ui->case1Label->setText("R' F'");
    ui->case3Label->setText("Line up with color and turn twice on the face");
    ui->hintTextLabel->setText("The goal of this first step is to get the 'white cross'. One trick is to get all "
                           "the white edges on the same side as the yellow center, then line up the "
                           "other color with its respective center, and turn that side twice. After doing "
                           "this with all four white edges, you should have the white cross!");


    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();
    ui->solvedLabel->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/White Cross/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/White Cross/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/White Cross/3.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/White Cross/4.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase1 method draws the correct labels, etc when model tells view it is on step 2 of learning
 */
void MainWindow::drawWhiteCornersStep(){

    hideAllLearningUI();
    showStepButtons();
    showAllStepLables();
    enableLastAndNextStepButtons();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();
    ui->hintLabel->show();
    ui->hintTextLabel->show();

    ui->case1Label->show();
    ui->case2Label->show();
    ui->case3Label->show();
    ui->case1Label->setText("R' D' R D R' D' R D R' D' R");
    ui->case2Label->setText("F D F'");
    ui->case3Label->setText("R' D' R");
    ui->hintTextLabel->setText("Now we need to put the white corners in. Find a corner piece with white in it, and "
                           "line it up with one of the three cases above. Perform that specific algorithm and it "
                           "will put the corner in the right spot. Do this four times for all four edges.");
    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();
    ui->solvedLabel->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/White Corners/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/White Corners/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/White Corners/3.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/White Corners/4.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase2 method draws the correct labels, etc when model tells view it is on step 2 of learning
 */
void MainWindow::drawSecondLayerStep(){
    showStepButtons();

    enableLastAndNextStepButtons();
    hideAllLearningUI();
    showStepButtons();
    showAllStepLables();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();
    ui->hintLabel->show();
    ui->hintTextLabel->show();


    ui->case1Label->show();
    ui->case2Label->show();
    //ui->case3Label->hide();
    ui->case1Label->setText("U R U' R' U' F' U F");
    ui->case2Label->setText("U' L' U L U F U' F'");
    ui->hintTextLabel->setText("Flip the cube so yellow is on top, and find an edge that doesn't contain "
                           "yellow on it. Line it up with one of the cases above and perform that "
                           "algorithm. Do it for all four non-yellow edges. If you don't have a "
                           "non-yellow edge on the top and the second layer isn't solved, do one "
                           "of the two algorithms above to move any yellow edge into that incorrect "
                           "spot and move the edge to its correct spot.");
    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();
    ui->solvedLabel->show();

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
    hideAllLearningUI();
    showStepButtons();
    showAllStepLables();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();
    ui->hintLabel->show();
    ui->hintTextLabel->show();

    ui->case1Label->show();
    ui->case2Label->show();
    ui->case3Label->show();
    ui->case1Label->setText("F U R U' R' F' U F R U R' U' F'");
    ui->case2Label->setText("F R U R' U' F'");
    ui->case3Label->setText("F U R U' R' F'");
    ui->hintTextLabel->setText("Now to solve the yellow cross. There are four different cases"
                           "you can have after solving the second layer: no yellow edges "
                           "facing up, two yellow edges in a reverse 'L' shape, two yellow "
                           "egdges in a '-' shape, and the yellow cross. If you don't have "
                           "the yellow cross already, orient your up side to the respective "
                           "picture and do the algorithm to get to the yellow cross.");
    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();
    ui->solvedLabel->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/Yellow Cross/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/Yellow Cross/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/Yellow Cross/3.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/Yellow Cross/4.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase4 method draws the correct labels, etc when model tells view it is on step 5 of learning
 */
void MainWindow::drawYellowCornerStep(){
    showStepButtons();

    enableLastAndNextStepButtons();
    ui->img1Label->show();
    ui->img2Label->hide();
    ui->img3Label->hide();
    ui->solvedLabel->show();


    ui->step1Label->show();
    ui->step2Label->hide();
    ui->step3Label->hide();
    ui->hintLabel->show();
    ui->hintTextLabel->show();
    ui->goalLabel->show();

    ui->case1Label->show();
    ui->case2Label->hide();
    ui->case3Label->hide();
    ui->case1Label->setText("R U R' U R U2 R'");
    ui->hintTextLabel->setText("Now that you have the yellow cross, your goal is to get your cube to have "
                           "one yellow corner up, and the rest out (like the image above). Performing "
                           "that algorithm will solve the yellow side. If you have the yellow cross and "
                           "you don't have that case, keep doing that algorithm above until you get that "
                           "case and then you'll solve the yellow side.");

    ui->img1Label->show();
    ui->solvedLabel->show();

    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/Yellow Corners/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/Yellow Corners/2.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::drawCase5 method draws the correct labels, etc when model tells view it is on step 6 of learning
 */
void MainWindow::drawThirdLayerStep(){
    showStepButtons();

    ui->lastButtonStep->setEnabled(true);
    ui->nextStepButton->setEnabled(false);


    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();
    ui->solvedLabel->show();

    ui->step1Label->show();
    ui->step2Label->show();
    ui->step3Label->show();
    ui->hintLabel->show();
    ui->hintTextLabel->show();
    ui->goalLabel->show();

    ui->case1Label->show();
    ui->case2Label->show();
    ui->case3Label->show();
    ui->case1Label->setText("U2 R' F R' B2 R F' R' B2 R2");
    ui->case2Label->setText("F2 U R' L F2 R L' U F2");
    ui->case3Label->setText("F2 U' R' L F2 R L' U' F2");
    ui->hintTextLabel->setText("You're almost done! Your goal now is to get \"headlights\", "
                           "or two corners of the same color together. Perform the first "
                           "algorithm above to solve all the corners. If you don't have "
                           "headlights, do the first algorithm anywhere and you'll get them. "
                           "After getting the headlights, allign the corners to be solved and "
                           "find which of the two cases you have above. If you don't have either, "
                           "perform either of the last two above and then you'll have one of the two cases.");
    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();
    ui->solvedLabel->show();
    ui->img1Label->setPixmap(QPixmap::fromImage(QImage(":/Third Layer/1.png").scaled(ui->img1Label->width(), ui->img1Label->height(), Qt::KeepAspectRatio)));
    ui->img2Label->setPixmap(QPixmap::fromImage(QImage(":/Third Layer/2.png").scaled(ui->img2Label->width(), ui->img2Label->height(), Qt::KeepAspectRatio)));
    ui->img3Label->setPixmap(QPixmap::fromImage(QImage(":/Third Layer/3.png").scaled(ui->img3Label->width(), ui->img3Label->height(), Qt::KeepAspectRatio)));
    ui->solvedLabel->setPixmap(QPixmap::fromImage(QImage(":/Third Layer/4.png").scaled(ui->solvedLabel->width(), ui->solvedLabel->height(), Qt::KeepAspectRatio)));

}

/*!
 * \brief MainWindow::showAllStepLables method draws labels that shows "step 1", "step 2", "step 3"
 */
void MainWindow::showAllStepLables(){
    ui->img1Label->show();
    ui->img2Label->show();
    ui->img3Label->show();
    ui->stepComboBox->show();
    ui->goalLabel->show();
}

/*!
 * \brief MainWindow::hideAllStepLabels method hides all step labels that show "step 1", "step 2", "step 3", all buttons, and images relating to teaching
 */
void MainWindow::hideAllLearningUI(){
    ui->lastButtonStep->hide();
    ui->nextStepButton->hide();
    ui->hintTextLabel->hide();

    ui->img1Label->hide();
    ui->img2Label->hide();
    ui->img3Label->hide();
    ui->solvedLabel->hide();
    ui->step1Label->hide();
    ui->step2Label->hide();
    ui->step3Label->hide();
    ui->hintLabel->hide();
    ui->case1Label->hide();
    ui->case2Label->hide();
    ui->case3Label->hide();
    ui->stepComboBox->hide();
    ui->goalLabel->hide();
    ui->notationLabel->hide();
}

/*!
 * \brief MainWindow::showStepButtons show all buttons related to steps and learning when clicked
 */
void MainWindow::showStepButtons()
{
    ui->lastButtonStep->show();
    ui->nextStepButton->show();
    ui->widget->show();
}

/*!
 * \brief MainWindow::on_learnButton_clicked method shows all buttons related to steps when clicked
 */
void MainWindow::on_learnButton_clicked()
{
    showStepButtons();
}

/*!
 * \brief MainWindow::enableLastAndNextStepButtons enables both next step and previous step buttons
 */
void MainWindow::enableLastAndNextStepButtons(){
    ui->lastButtonStep->setEnabled(true);
    ui->nextStepButton->setEnabled(true);
}

/*!
 * \brief MainWindow::eventFilter filter for all letter buttons that dictates what occurs when we hover over and off buttons
 * \param obj button to apply filter on
 */
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // This function repeatedly call for those QObjects
    // which have installed eventFilter (Step 2)

    //clockwise face moves
    if(ui->openGLWidget->isVisible()){
        if (obj == (QObject*)ui->fButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->fArrowLabel->show();
                ui->fArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/fButtonArrow.png").scaled(ui->fArrowLabel->width(), ui->fArrowLabel->height(), Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->fArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->rButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->rArrowButton->show();
                ui->rArrowButton->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/rButtonArrow.png").scaled(ui->rArrowButton->width(), ui->rArrowButton->height(), Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->rArrowButton->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->uButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->uArrowLabel->show();
                ui->uArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/uButtonArrow.png").scaled(ui->uArrowLabel->width(), ui->uArrowLabel->height(), Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->uArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->bButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->bArrowLabel->show();
                ui->bArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/bButtonArrow.png").scaled(ui->bArrowLabel->width(), ui->bArrowLabel->height(), Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->bArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->lButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->lArrowLabel->show();
                ui->lArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/lButtonArrow.png").scaled(ui->lArrowLabel->width(), ui->lArrowLabel->height(), Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->lArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->dButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->dArrowLabel->show();
                ui->dArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/dButtonArrow.png").scaled(ui->dArrowLabel->width(), ui->dArrowLabel->height(), Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->dArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        //counterclockwise face moves
        if (obj == (QObject*)ui->fPrimeButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->fArrowLabel->show();
                ui->fArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/fPrimeButtonArrow.png").scaled(ui->fArrowLabel->width(), ui->fArrowLabel->height(), Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->fArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->rPrimeButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->rArrowButton->show();
                ui->rArrowButton->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/rPrimeButtonArrow.png").scaled(60,60, Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->rArrowButton->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->uPrimeButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->uArrowLabel->show();
                ui->uArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/uButtonArrow.png").scaled(ui->uArrowLabel->width(), ui->uArrowLabel->height(), Qt::KeepAspectRatio).mirrored(true, false)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->uArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->bPrimeButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->bPrimeArrowLabel->show();
                ui->bPrimeArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/bPrimeButtonArrow.png").scaled(70,70, Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->bPrimeArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->lPrimeButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->lArrowLabel->show();
                ui->lArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/lPrimeButtonArrow.png").scaled(ui->lArrowLabel->width(), ui->lArrowLabel->height(), Qt::KeepAspectRatio)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->lArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }

        if (obj == (QObject*)ui->dPrimeButton) {
            if (event->type() == QEvent::Enter)
            {
                ui->dArrowLabel->show();
                ui->dArrowLabel->setPixmap(QPixmap::fromImage(QImage(":/buttonArrows/dButtonArrow.png").scaled(ui->dArrowLabel->width(), ui->dArrowLabel->height(), Qt::KeepAspectRatio).mirrored(true, false)));
            }
            if (event->type() == QEvent::Leave)
            {
                ui->dArrowLabel->hide();
            }
            return QWidget::eventFilter(obj, event);
        }
    }
}



