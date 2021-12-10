#ifndef HEADBOX2D_H
#define HEADBOX2D_H

#include <QWidget>
#include <box2d/include/box2d/box2d.h>
#include <QTimer>
#include <QPainter>


class headBox2D : public QWidget
{
    Q_OBJECT
public:
    explicit headBox2D(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
signals:

public slots:
    void updateWorld();

private:
    b2World world;
    b2Body* body;
    QTimer timer;
    QImage image;
};
#endif // HEADBOX2D_H
