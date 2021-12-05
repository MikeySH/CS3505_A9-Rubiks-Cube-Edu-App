#ifndef FACES_H
#define FACES_H
#include <QVector>
#include <QMatrix3x3>
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
    //constructor
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
    QVector<QColor> getRow(int);
    QVector<QColor> getCol(int);

    void rotateClockwise();
    void rotateCounterClockwise();

};

#endif // FACES_H
