#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTableWidget>
#include <QDebug>
#include <QVector>
#include "complex.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool sravnenie(Complex &c);
    bool sravnenie1(Complex &c);
    bool Swap(int i, int j);
    void vvod_matrici();
    void vivod_matrici();
    int Ne_nol(int z);
    bool Rang();
    void PryamoiHod();
    void ObratniHod();
    void Vivod_Otvetov();

private:
    int col; //столбцы
    int row; //строки
    Complex **mtr; //матрица
    Complex *b; //столбец ответов
    //QVector<QVector <Complex>> mtr;
    //QVector <Complex> b;
    Ui::MainWindow *ui;
private slots:
    void create_matrix();
    void consider();
};

#endif // MAINWINDOW_H
