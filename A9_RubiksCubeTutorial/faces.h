#ifndef FACES_H
#define FACES_H
#include <QVector>
#include <QMatrix3x3>
#include <QImage>



class Faces
{
public:
    Faces() = default;
    Faces(QColor);
    QImage colorPicture;
    QVector<QColor> swapRow(int,  QVector<QColor> );
    QVector<QColor> swapCollumn(int,  QVector<QColor>);
    QColor getColorCorrespondingToInt(int, int);


};

#endif // FACES_H
