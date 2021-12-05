#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "mainwidget.h"
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE
/*!
 * \brief The MainWindow class mainwindow class that handles view and control of this rubic's cube
 * project
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    Model modelObj;
    // sends key events to 3d drawer
    void keyPressEvent(QKeyEvent *event);

signals:
    void saveName();
    void rotateRight();
    void rotateLeft();

private slots:
    // reacts when left button is selected  - moves 3d cube left by one face
    void on_moveCubeLeft_clicked();
    // evoked when right button clicks - moves 3d cube right by one face
    void on_moveCubeRight_clicked();
    // evoked when flip button clicked - flips cube
    void on_flipButton_clicked();
    void on_perspective2DButton_clicked();
    void on_perspective3DButton_clicked();
};
#endif // MAINWINDOW_H
