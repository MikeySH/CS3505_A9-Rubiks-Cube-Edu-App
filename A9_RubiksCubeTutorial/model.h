#ifndef MODEL_H
#define MODEL_H
#include "faces.h"
#include <QColor>
#include <QPainter>

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

private:
void makeGrid(Faces);




public slots:
void updateFaces();
void frontMove();

signals:
    void sendFrontGrid(QPixmap);
    void sendBackGrid(QPixmap);
    void sendUpGrid(QPixmap);
    void sendDownGrid(QPixmap);
    void sendLeftGrid(QPixmap);
    void sendRightGrid(QPixmap);

};

#endif // MODEL_H
