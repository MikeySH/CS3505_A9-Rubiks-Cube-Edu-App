#ifndef FACES_H
#define FACES_H
#include <QVector>
#include <QMatrix3x3>
#include <QImage>



class Faces
{
private:
    QString name;

public:
    Faces() = default;
    Faces(QColor, QString);
    QImage colorPicture;
    QVector<QColor> swapRow(int,  QVector<QColor> );
    QVector<QColor> swapCollumn(int,  QVector<QColor>);
    QColor getColorCorrespondingToInt(int, int);

    QImage getImage();
    QString getName();

};

#endif // FACES_H
