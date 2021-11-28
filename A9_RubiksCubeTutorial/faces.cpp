#include "faces.h"

Faces::Faces(QColor thisOriginalColor)
{

    colorPicture = QImage(3,3, QImage::Format_RGBA64);
    colorPicture.fill(thisOriginalColor);
}

QColor Faces::getColorCorrespondingToInt(int x, int y){
    colorPicture.pixelColor(x, y);
}

QVector<QColor> Faces::swapRow(int rowNumber, QVector<QColor> row){
    QVector<QColor> temp;

    for (int i=0; i<3; i++){

        temp[i] =  colorPicture.pixelColor(i,rowNumber);
        colorPicture.setPixelColor(i, rowNumber, row[i]);
    }

    return temp;
}

QVector<QColor> Faces::swapCollumn(int colNumber,  QVector<QColor> col ){

    QVector<QColor> temp;

    for (int i=0; i<3; i++){

        temp[i] =  colorPicture.pixelColor(colNumber,i);
        colorPicture.setPixelColor(colNumber, i, col[i]);
    }

    return temp;
}
