#include "model.h"
#include <QBrush>


//remove later
#include <iostream>
using namespace std;



Model::Model(QObject *parent) : QObject(parent)
{
    front = Faces(Qt::green, "front");
    back = Faces(Qt::blue, "back");
    up = Faces(Qt::white, "up"); //QColor(255,165,0)
    down = Faces(Qt::yellow, "down");
    left = Faces(QColor(255,165,0), "left");
    right = Faces(Qt::red, "right");
}


/*!
 * \brief Model::makeGrid makes the grid for the sprite drawing.
 * \param canvasSize size of the canvas/preview drawing of sprite
 */
void Model::makeGrid(Faces face ){
    // add grid lines on top of sprite image's pixmap
    QPixmap pixmap(QPixmap::fromImage(face.getImage()).scaled(180, 180, Qt::KeepAspectRatio));
    QPainter painter(&pixmap);
    // use black as the line color
    painter.setPen(QColor(0, 0, 0, 255));

    // draw vertical and horizontal lines
    for(float lineIndex = 0; lineIndex <= pixmap.width(); lineIndex+=pixmap.width()/3){
        //vertical lines
        painter.drawLine(lineIndex, 0, lineIndex, pixmap.height());
        //horizontal lines
        painter.drawLine(0, lineIndex, pixmap.width(), lineIndex);

    }
    // send grid to view to draw
    if (face.getName() == "front"){
        emit sendFrontGrid(pixmap);
    } else if (face.getName() == "back"){
        emit sendBackGrid(pixmap);
    } else if (face.getName() == "up"){
        emit sendUpGrid(pixmap);
    } else if (face.getName() == "down"){
        emit sendDownGrid(pixmap);
    } else if (face.getName() == "left"){
        emit sendLeftGrid(pixmap);
    } else {
        emit sendRightGrid(pixmap);
    }
}

void Model::updateFaces(){
    makeGrid(front);
    makeGrid(back);
    makeGrid(up);
    makeGrid(down);
    makeGrid(left);
    makeGrid(right);
}

void Model::frontMove(){
    //up
 //left  //right
    //down

   // QVector<QColor> temp = up.swapRow(2, left.getCol(2)); //sets up to left row
    QVector<QColor> temp = left.getCol(2); //sets up to left row
    QVector<QColor> temp2 = down.getRow(0); //sets up to left row
    QVector<QColor> temp3 = right.getCol(0); //sets up to left row
    QVector<QColor> temp4 = up.getRow(2); //sets up to left row

//    left.swapColumn(2, down.getRow(0)); //sets left to down col
//    down.swapRow(0, right.getCol(0)); //sets down to right col
//    right.swapColumn(0, temp); //sets right to up row

    up.swapRow(2, temp);
    left.swapColumn(2, temp2);
    down.swapRow(0, temp3);
    right.swapColumn(0, temp4);

    //rotate front 90 degrees;
    front.rotateClockwise();

    updateFaces();
}

void Model::rightMove(){
    //up
    //front    //back
    //down

//    QVector<QColor> temp = back.swapColumn(0, up.getCol(2));
//    up.swapColumn(2, front.getCol(2));
//    front.swapColumn(2, down.getCol(2));
//    down.swapColumn(2, temp);

    QVector<QColor> temp = up.getCol(2); //sets up to left row
    QVector<QColor> temp2 = front.getCol(2); //sets up to left row
    QVector<QColor> temp3 = down.getCol(2); //sets up to left row
    QVector<QColor> temp4 = back.getCol(0); //sets up to left row

    up.swapColumn(2, temp2);
    front.swapColumn(2, temp3);
    down.swapColumn(2, temp4);
    back.swapColumn(0, temp);

    //rotate front 90 degrees;
    right.rotateClockwise();

    updateFaces();
}
