/*
 * Jimmy Trinh && Jacob Day && Amitoj Singh && Michael Shin
 * Software Practice II, CS 3505
 * Fall 2021
 * A9: An Educational App
 */

#ifndef MODEL_H
#define MODEL_H
#include "faces.h"
#include <QColor>
#include <QPainter>
#include <QRandomGenerator>
#include <QTimer>
#include <QTime>

/*!
 * \brief The Model class handles all of the rubik's cube logic and sends whatever data the View needs.
 */
class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    Faces front; // front face of the cube
    Faces back; // back face of the cube
    Faces up; // up face of the cube
    Faces down; // down face of the cube
    Faces left; // left face of the cube
    Faces right; // right face of the cube

    int currStep; // current step in the tutorial

private:
    // method draws grids of all faces
    void makeGrid(Faces);
    // Checks if the Rubik's Cube is in a solved state.
    bool isSolved();
    // Resets the time-to-solve timer when reset button is pressed.
    void fixTimerIfResetPressed();
    // check if the best time is 0.
    bool isBestTimeZero();
    // boolean for checking if the rubik's cube is solved.
    bool isScrambled = false;
    // timer for keeping track of the user's best time.
    QTimer* timer = new QTimer();
    // Time variable to send to view
    QTime time;
    // Best time so far
    QTime bestTime;



public slots:
    // handles redrawing of faces
    void updateFaces();
    // handles moving front face clockwise
    void frontMove();
    // handles moving right face clockwise
    void rightMove();
    // handles moving up face clockwise
    void upMove();
    // handles moving back face clockwise
    void backMove();
    // handles moving left face clockwise
    void leftMove();
    // handles moving down face clockwise
    void downMove();
    // handles counterclockwise moving of the front face
    void frontMovePrime();
    // handles counterclockwise moving of the right face
    void rightMovePrime();
    // handles counterclockwise moving of the up face
    void upMovePrime();
    // handles counterclockwise moving of the back face
    void backMovePrime();
    // handles counterclockwise moving of the left face
    void leftMovePrime();
    // handles counterclockwise moving of the down face
    void downMovePrime();
    // scrambles faces
    void scramble();
    // resets faces to classic rubic's cube faces
    void resetFaces();
    // save state of cube
    void save();
    // increments current step
    void incrementStep();
    // set index of step
    void setStep(int);
    // decrements current step
    void decrementStep();
    // begin tutorial
    void startTutorial();

    // rotates the cube to the right
    void rotateRight();
    // rotates the cube to the left
    void rotateLeft();
    // flips cube to the opposite faces not being shown
    void flip();

    // updates timer by one second
    void updateCountdown();
    // stops the updateing of the timer keeping track of solving time
    void stopUpdateCountdown();
    // responds to dev tool button, scrambles one way
   void devToolScramble();

signals:
    // signal that handles sending the front face of cube
    void sendFrontGrid(QPixmap);
    // signal that handles sending the back face of cube
    void sendBackGrid(QPixmap);
    // signal that handles sending the up face of cube
    void sendUpGrid(QPixmap);
    // signal that handles sending the down face of cube
    void sendDownGrid(QPixmap);
    // signal that handles sending the left face of cube
    void sendLeftGrid(QPixmap);
    // signal that handles sending the right face of cube
    void sendRightGrid(QPixmap);
    // update step label
    void sendStep(int);
    // send image to view
    void sendImage(QImage);
    // let view know about reset cube
    void resetCube();
    // signal that starts the celebration screen
    void showAnimation();
    // sends string of current time taken to view
    void sendCurrentTime(QString);

};

#endif // MODEL_H
