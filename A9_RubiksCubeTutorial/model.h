#ifndef MODEL_H
#define MODEL_H
#include "faces.h"
#include <QColor>
#include <QPainter>
#include <QRandomGenerator>

/*!
 * \brief The Model class class handles all rubic's cube ui data
 */
class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    Faces front;
    Faces back;
    Faces up;
    Faces down;
    Faces left;
    Faces right;

    QVector<QString> steps;
    int currStep;

private:
    // method draws grids of all faces
    void makeGrid(Faces);

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

    void save(QString);
    // changes current step
   // void incrementStep();

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
   // void sendStep(QString);

};

#endif // MODEL_H
