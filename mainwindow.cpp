#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QTextEdit>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // *label = new QLabel(this);

    //create nxn 2d vector of textboxes
    QVector<QVector<QTextEdit*>> cellTextBoxes(boardSize);
    for(int row = 0; row < boardSize; row++){
        cellTextBoxes.push_back(QVector<QTextEdit*>());
        for(int col = 0; col < boardSize; col++){
            cellTextBoxes[row].resize(boardSize);
            QTextEdit * curTextBox = new QTextEdit(this);
            //set textbox position
            curTextBox->move(baseBoardX + row*textBoxSpacing, baseBoardY + col*textBoxSpacing);
            //set textbox size
            curTextBox->setMaximumSize(textBoxSize, textBoxSize);
            cellTextBoxes[row][col] = curTextBox;
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

