#include "faces.h"

//remove later
#include <iostream>
using namespace std;

Faces::Faces(QColor thisOriginalColor, QString name)
{
    this->name = name;
    colorPicture = QImage(3,3, QImage::Format_RGBA64);
    colorPicture.fill(thisOriginalColor);
}

QColor Faces::getColorCorrespondingToInt(int x, int y){
    colorPicture.pixelColor(x, y);
}

QVector<QColor> Faces::swapRow(int rowNumber, QVector<QColor> row){
    QVector<QColor> temp;

    for (int i=0; i<3; i++){

        temp.push_back(colorPicture.pixelColor(i,rowNumber));
        colorPicture.setPixelColor(i, rowNumber, row[i]);
    }

    return temp;
}

QVector<QColor> Faces::swapColumn(int colNumber,  QVector<QColor> col ){

    QVector<QColor> temp;

    for (int i=0; i<3; i++){

        temp.push_back(colorPicture.pixelColor(colNumber,i));
        colorPicture.setPixelColor(colNumber, i, col[i]);
    }
    return temp;
}

QImage Faces::getImage(){
    return colorPicture;
}

QString Faces::getName(){
    return name;
}

QVector<QColor> Faces::getRow(int rowNum){
    QVector<QColor> temp;

    for (int i=0; i<3; i++){
        temp.push_back(colorPicture.pixelColor(i,rowNum));
    }

    return temp;
}

QVector<QColor> Faces::getCol(int colNum){
    QVector<QColor> temp;

    for (int i=0; i<3; i++){

        temp.push_back(colorPicture.pixelColor(colNum,i));
    }

    return temp;
}

void Faces::rotateClockwise(){
//    QVector<QColor> temp = swapRow(2, getCol(2));
//    swapColumn(2, getRow(0));
//    swapRow(0, getCol(0));
//    swapColumn(0, temp);

    QVector<QColor> temp = getCol(0);
    QVector<QColor> temp1 = getCol(2);
    QVector<QColor> temp2 = getRow(0);
    QVector<QColor> temp3 = getRow(2);

    swapColumn(2, temp3);
    swapColumn(0, temp);
    swapRow(2, temp2);
    swapRow(0, temp1);


}
