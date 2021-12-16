/*
 * Jimmy Trinh && Jacob Day && Amitoj Singh && Michael Shin
 * Software Practice II, CS 3505
 * Fall 2021
 * A9: An Educational App
 * Video: Video: https://youtu.be/uIMg9xUNVgY
 */

#ifndef FACES_H
#define FACES_H
#include <QVector>
#include <QImage>

/*!
 * \brief The Faces class Class representing the faces of a rubic's cube
 */
class Faces
{
private:
    QString name;
    QImage colorPicture;

public:
    // constructors
    Faces() = default;
    Faces(QColor, QString);
    Faces(const Faces&);

    // swap methods
    QVector<QColor> swapRow(int,  QVector<QColor> );
    QVector<QColor> swapColumn(int,  QVector<QColor>);
    QColor getColorCorrespondingToInt(int, int);

    // class getters
    QImage getImage();
    QString getName();
    void setName(QString);
    QVector<QColor> getRow(int);
    QVector<QColor> getCol(int);

    // rotation methods
    void rotateClockwise();
    void rotateCounterClockwise();
};

#endif // FACES_H
