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
    // Traverse each cycle
        for(int k = 0; k < 3; k ++){
            for (int i = 0; i < 3 / 2; i++) {
                for (int j = i; j < 3 - i - 1; j++) {

                    // Swap elements of each cycle
                    // in clockwise direction
                    QColor temp = colorPicture.pixelColor(i,j);

                    colorPicture.setPixelColor(i,j, colorPicture.pixelColor(3 - 1 - j, i));
                    colorPicture.setPixelColor(3 - 1 - j, i, colorPicture.pixelColor(3 - 1 - i,3 - 1 - j));
                    colorPicture.setPixelColor(3 - 1 - i, 3 - 1 - j,  colorPicture.pixelColor(j, 3 - 1 - i));
                    colorPicture.setPixelColor(j, 3 - 1 - i, temp);
                }
            }
        }
}
