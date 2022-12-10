#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    const int baseBoardX = 50;
    const int baseBoardY = 50;
    int boardSize = 9;
    const int textBoxSpacing = 50;
    const int textBoxSize = 25;
};
#endif // MAINWINDOW_H
