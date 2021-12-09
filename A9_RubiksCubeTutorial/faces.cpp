#include "faces.h"

//remove later
#include <iostream>
using namespace std;

/*!
 * \brief Faces::Faces Constructs the face object that is used to represent Rubics faces
 * \param thisOriginalColor The original color of the face
 * \param name the name of the face (front, back, right, etc)
 */
Faces::Faces(QColor thisOriginalColor, QString name)
{
    this->name = name;
    colorPicture = QImage(3,3, QImage::Format_RGBA64);
    colorPicture.fill(thisOriginalColor);
}

Faces::Faces(const Faces& other)
{
    this->colorPicture = other.colorPicture;
    this->name = other.name;
}

//void Faces::setColor(int x, int y, QColor color){
//    colorPicture.setPixelColor(x,y,color);
//}

/*!
 * \brief Faces::getColorCorrespondingToInt Returns color at given pixel of face
 * \param x x pos of color inquiry
 * \param y y pos of color inquiry
 * \return color at coordinate
 */
QColor Faces::getColorCorrespondingToInt(int x, int y){
    return colorPicture.pixelColor(x, y);
}

/*!
 * \brief Faces::swapRow swaps given vector of values with row given to swap
 * \param rowNumber the row number that is being swapped to
 * \param row values containing what values will be changed to
 * \return the vector of colors that are changed from and replaced
 */
QVector<QColor> Faces::swapRow(int rowNumber, QVector<QColor> row){
    QVector<QColor> temp;

    // collect all old colors in row and then replace them
    for (int i=0; i<3; i++){
        temp.push_back(colorPicture.pixelColor(i,rowNumber));
        colorPicture.setPixelColor(i, rowNumber, row[i]);
    }

    return temp;
}

/*!
 * \brief Faces::swapColumn swaps given vector of values with col given to swap
 * \param colNumber the collumn number that is to be swapped
 * \param col the collumn being sweapped to
 * \return  the vector of colors that are changed from
 */
QVector<QColor> Faces::swapColumn(int colNumber,  QVector<QColor> col ){

    QVector<QColor> temp;

    // collect all old colors in col and then replace them
    for (int i=0; i<3; i++){
        temp.push_back(colorPicture.pixelColor(colNumber,i));
        colorPicture.setPixelColor(colNumber, i, col[i]);
    }
    return temp;
}

/*!
 * \brief Faces::getImage return the given image represented by this face
 * \return the image
 */
QImage Faces::getImage(){
    return colorPicture;
}

/*!
 * \brief Faces::getName returns the name of given face
 */
QString Faces::getName(){
    return name;
}

void Faces::setName(QString otherName){
    name = otherName;
}

/*!
 * \brief Faces::getRow returns vector of colors represented by the row inquired for
 * \param rowNum row number that colors will be returned from
 */
QVector<QColor> Faces::getRow(int rowNum){
    QVector<QColor> temp;

    // collect all colors corresponding to inquired row
    for (int i=0; i<3; i++)
        temp.push_back(colorPicture.pixelColor(i,rowNum));


    return temp;
}

/*!
 * \brief Faces::getCol returns the columns of colors at given index of image
 * \param colNum column number that colors will be returned from
 * \return
 */
QVector<QColor> Faces::getCol(int colNum){
    QVector<QColor> temp;

    // collect all colors correspond to inquired col
    for (int i=0; i<3; i++)
        temp.push_back(colorPicture.pixelColor(colNum,i));


    return temp;
}

/*!
 * \brief Faces::rotateClockwise rotates current face clockwise
 */
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

/*!
 * \brief Faces::rotateCounterClockwise Rotates current face counterclockwise
 */
void Faces::rotateCounterClockwise(){
    for(int i = 0; i < 3; i++){
        rotateClockwise();
    }
}
