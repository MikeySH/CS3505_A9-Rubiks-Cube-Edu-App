/*
 * Jimmy Trinh && Jacob Day && Amitoj Singh && Michael Shin
 * Software Practice II, CS 3505
 * Fall 2021
 * A9: An Educational App
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "cube3Dwidget.h"
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE
/*!
 * \brief The MainWindow class mainwindow class that handles view and control of this rubic's cube
 * project
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Model modelObj;
    // sends key events to 3d drawer
    void keyPressEvent(QKeyEvent *event);
    // method for the cube pieces step
    void drawCubePiecesStep();
    // method for the button moves step
    void drawButtonMovesStep();
    // method for the white cross step
    void drawWhiteCrossStep();
    // method for the white cornerstep
    void drawWhiteCornersStep();
    // method for the second layerstep
    void drawSecondLayerStep();
    // method for the yellow crossstep
    void drawYellowCrossStep();
    // method for the yellow corner step
    void drawYellowCornerStep();
    // method for the third layer step
    void drawThirdLayerStep();
    // helper for showing all learning / step labels
    void showAllStepLabels();
    // helper for hiding all learning / step labels
    void hideAllLearningUI();
    // enables the next and last buttons in the learning tutorial
    void enableLastAndNextStepButtons();
    // it's an event filter for buttons
    bool eventFilter(QObject *obj, QEvent *event);
    // show the step buttons
    void showStepButtons();

signals:
    // rotates cube right
    void rotateRight();
    // rotates cube left
    void rotateLeft();
    // flips cube
    void flip();
    // starts tutorial
    void initiateTutorial();

private slots:
    // reacts when left button is selected  - moves 3d cube left by one face
    void on_moveCubeLeft_clicked();
    // evoked when right button clicks - moves 3d cube right by one face
    void on_moveCubeRight_clicked();
    // evoked when flip button clicked - flips cube
    void on_flipButton_clicked();
    // changes Rubik's Cube to 2D view
    void on_perspective2DButton_clicked();
    // changes Rubik's Cube to 3D view
    void on_perspective3DButton_clicked();
    // starts the Rubik's Cube tutorial
    void on_learnButton_clicked();

public slots:
    // Shows the current tutorial step
    void showCurrentStep(int);
};
#endif // MAINWINDOW_H
