#ifndef MODEL_H
#define MODEL_H
#include "faces.h"
#include <QColor>
#include <QPainter>

class Model
{

private:
void makeGrid(Faces);

public:
    Model();

Faces front;
Faces back;
Faces top;
Faces bottom;
Faces left;
Faces right;

signals:
    void sendFrontGrid(QPixmap);
    void sendBackGrid(QPixmap);
    void sendTopGrid(QPixmap);
    void sendBottomGrid(QPixmap);
    void sendLeftGrid(QPixmap);
    void sendRightGrid(QPixmap);

};

#endif // MODEL_H
