#include "model.h"
#include <QBrush>


//remove later
#include <iostream>
using namespace std;



Model::Model(QObject *parent) : QObject(parent)
{
   resetFaces();
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

    QVector<QColor> temp = left.getCol(2); //sets up to left row
    QVector<QColor> temp2 = down.getRow(0); //sets up to left row
    QVector<QColor> temp3 = right.getCol(0); //sets up to left row
    QVector<QColor> temp4 = up.getRow(2); //sets up to left row
    QVector<QColor> temp5;
    QVector<QColor> temp6;


    for(int i =0; i < 3; i++){
        temp5.push_front(temp3[i]);
        temp6.push_front(temp[i]);
    }

    up.swapRow(2, temp6);
    left.swapColumn(2, temp2);
    down.swapRow(0, temp5);
    right.swapColumn(0, temp4);

    //rotate front 90 degrees;
    front.rotateClockwise();

    updateFaces();
}

void Model::rightMove(){
    //up
    //front    //back
    //down

    QVector<QColor> temp = up.getCol(2); //sets up to left row
    QVector<QColor> temp2 = front.getCol(2); //sets up to left row
    QVector<QColor> temp3 = down.getCol(2); //sets up to left row
    QVector<QColor> temp4 = back.getCol(0); //sets up to left row
    QVector<QColor> temp5;
    QVector<QColor> temp6;

    for(int i =0; i < 3; i++){
        temp5.push_front(temp4[i]);
        temp6.push_front(temp[i]);
    }

    up.swapColumn(2, temp2);
    front.swapColumn(2, temp3);
    down.swapColumn(2, temp5);
    back.swapColumn(0, temp6);

    //rotate front 90 degrees;
    right.rotateClockwise();

    updateFaces();
}


void Model::upMove(){
//left front right back

    QVector<QColor> temp = left.getRow(0);
    QVector<QColor> temp2 = front.getRow(0);
    QVector<QColor> temp3 = right.getRow(0);
    QVector<QColor> temp4 = back.getRow(0);


    left.swapRow(0, temp2);
    front.swapRow(0, temp3);
    right.swapRow(0, temp4);
    back.swapRow(0, temp);

    //rotate front 90 degrees;
    up.rotateClockwise();

    updateFaces();
}

void Model::backMove()
{
    // QVector<QColor> temp = up.swapRow(2, left.getCol(2)); //sets up to left row
     QVector<QColor> temp = left.getCol(0); //sets up to left row
     QVector<QColor> temp2 = down.getRow(2); //sets up to left row
     QVector<QColor> temp3 = right.getCol(2); //sets up to left row
     QVector<QColor> temp4 = up.getRow(0); //sets up to left row
     QVector<QColor> temp5;
     QVector<QColor> temp6;


     for(int i =0; i < 3; i++){
         temp5.push_front(temp4[i]);
         temp6.push_front(temp2[i]);
     }
 //    left.swapColumn(2, down.getRow(0)); //sets left to down col
 //    down.swapRow(0, right.getCol(0)); //sets down to right col
 //    right.swapColumn(0, temp); //sets right to up row

     up.swapRow(0, temp3);
     left.swapColumn(0, temp5);
     down.swapRow(2, temp);
     right.swapColumn(2, temp6);

     //rotate front 90 degrees;
     back.rotateClockwise();

     updateFaces();

}

void Model::leftMove(){

    QVector<QColor> temp = up.getCol(0); //sets up to left row
    QVector<QColor> temp2 = front.getCol(0); //sets up to left row
    QVector<QColor> temp3 = down.getCol(0); //sets up to left row
    QVector<QColor> temp4 = back.getCol(2); //sets up to left row
    QVector<QColor> temp5;
    QVector<QColor> temp6;

    for(int i =0; i < 3; i++){
        temp5.push_front(temp4[i]);
        temp6.push_front(temp3[i]);
    }

    up.swapColumn(0, temp5);
    front.swapColumn(0, temp);
    down.swapColumn(0, temp2);
    back.swapColumn(2, temp6);

    //rotate front 90 degrees;
    left.rotateClockwise();

    updateFaces();
}

void Model::downMove(){

    QVector<QColor> temp = back.getRow(2);
    QVector<QColor> temp2 = front.getRow(2);
    QVector<QColor> temp3 = left.getRow(2);
    QVector<QColor> temp4 = right.getRow(2);

    left.swapRow(2, temp);
    front.swapRow(2, temp3);
    right.swapRow(2, temp2);
    back.swapRow(2, temp4);
    //rotate front 90 degrees;
    down.rotateClockwise();

    updateFaces();
}

void Model::frontMovePrime(){
 for(int i =0; i<3;i++)
     frontMove();
}

void Model::rightMovePrime(){
 for(int i =0; i<3;i++)
     rightMove();
}

void Model::upMovePrime(){
 for(int i =0; i<3;i++)
     upMove();
}

void Model::backMovePrime(){
 for(int i =0; i<3;i++)
     backMove();
}

void Model::leftMovePrime(){
 for(int i =0; i<3;i++)
     leftMove();
}

void Model::downMovePrime(){
 for(int i =0; i<3;i++)
     downMove();
}




void Model::scramble(){

    for(int i=0; i< 100; i++){
        // get random number that corresponds to a value
        int v = QRandomGenerator::global()->bounded(1, 7);

        switch(v){
        case 1:
            leftMove();
            break;
        case 2:  frontMove();
            break;
        case 3:  rightMove();
            break;
        case 4: upMove();
            break;
        case 5: backMove();
            break;
        case 6: downMove();
            break;
        }
    }

}


void Model::resetFaces(){

    front = Faces(Qt::green, "front");
    back = Faces(Qt::blue, "back");
    up = Faces(Qt::white, "up"); //QColor(255,165,0)
    down = Faces(Qt::yellow, "down");
    left = Faces(QColor(255,165,0), "left");
    right = Faces(Qt::red, "right");
    updateFaces();
}

