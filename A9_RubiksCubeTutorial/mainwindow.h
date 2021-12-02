#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "model.h"
#include "mainwidget.h"

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

signals:
    void saveName();

};
#endif // MAINWINDOW_H
