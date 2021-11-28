#include "model.h"
#include <QBrush>



Model::Model(QObject *parent) : QObject(parent)
{
    front = Faces(Qt::green, "front");
    back = Faces(Qt::blue, "back");
    top = Faces(Qt::white, "top"); //QColor(255,165,0)
    bottom = Faces(Qt::yellow, "bottom");
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
    } else if (face.getName() == "top"){
        emit sendTopGrid(pixmap);
    } else if (face.getName() == "bottom"){
        emit sendBottomGrid(pixmap);
    } else if (face.getName() == "left"){
        emit sendLeftGrid(pixmap);
    } else {
        emit sendRightGrid(pixmap);
    }
}

void Model::updateFaces(){
    makeGrid(front);
    makeGrid(back);
    makeGrid(top);
    makeGrid(bottom);
    makeGrid(left);
    makeGrid(right);


}
