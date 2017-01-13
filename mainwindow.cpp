#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->create_btn,SIGNAL(clicked()),this,SLOT(create_matrix())); //соеденяем кнопку создания матрицы с функцией
    connect(ui->consider_btn,SIGNAL(clicked()),this,SLOT(consider())); //соеденяем кнопку считать с функцией
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::create_matrix()
{
    col = ui->col->text().toInt();
    row = ui->row->text().toInt();
    // Создание Таблицы

    QStringList head; //создаем шапку таблицы
    for(int i=1; i < col; i++)
    {
        QString str_x = "x";
        head << str_x.append(QString::number(i));
    }
    head << "b";


    ui->tableWidget->setRowCount(row); // указываем количество строк
    ui->tableWidget->setColumnCount(col); // указываем количество столбцов плюс столбец ответов
    ui->tableWidget->setHorizontalHeaderLabels(head); //задаем шапку

    // выделяем память под все ячейки таблицы
    for(int stroka = 0; stroka <  row; stroka++)
      for(int stolbeu = 0; stolbeu <  col+1; stolbeu++)
            ui->tableWidget->setItem(stroka, stolbeu, new QTableWidgetItem());


    // выделяем память под все ячейки таблицы
    for(int stroka = 0; stroka < row; stroka++)
      for(int stolbeu = 0; stolbeu < col+1; stolbeu++)
      {
           QTableWidgetItem *item = new QTableWidgetItem(); // выделяем память под ячейку
           item->setText(QString("0")); // вставляем текст
           ui->tableWidget->setItem(stroka, stolbeu, item); // вставляем ячейку
      }
    ui->start_page->hide();
    ui->matrix_page->show();
}
void MainWindow::consider()
{
   /*
    //создадим два двумерных массива с реальной и мнимой частью всех ячеек
    double **Re;
    double **Im;
    //выделем память
    Re = new double* [row];
    Im = new double* [row];
    for (int i = 0; i < row; i++)
    {
      Re[i] = new double [col];
    }
    for (int i = 0; i < row; i++)
    {
      Im[i] = new double [col];
    }
    for(int stroka = 0; stroka < row; stroka++)
      for(int stolbeu = 0; stolbeu < col; stolbeu++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(stroka,stolbeu); //получим ячейку с индексами
        QString text = item->text(); //получим текст ячейки
        QStringList list = text.split("+"); //разделим на две части по +
        list[1].chop(1);//удалим i в конце
        Re[stroka][stolbeu] = list[0].toDouble(); //сделаем преобразование в double
        Im[stroka][stolbeu] = list[1].toDouble();
    }
    qDebug() << Re[1][1] << "+" << Im[1][1] << "i"; //для примера выведу в консоль элемент из второй строки второго столбца

   //здесь будешь считать

    QString res = "Ответ: x1= , x2= "; //здесь будет твой ответ
    ui->result->setText(res);
    */

    //*
    mtr = new Complex *[col];
    for (int i = 0; i < row; i++)
    {
        mtr[i] = new Complex[row];
    }
    b = new Complex[col];
    //*/


    /*
    b.reserve(row);
    mtr.reserve(row);
    for (int i = 0; i < row; i++)
    {
        mtr[i].reserve(col);
    }
    */

    vvod_matrici();//заполняем 2 массива значениями
    PryamoiHod();//выполняем прямой ход метода Гаусса
    //vivod_matrici(mtr, n, b, m);//выводим результат
    if (!Rang())//закидываем результат прямого хода в функцию для проверки ранга, если rang[A] < rang[A|b] то выводим на экран сообщение о несовместности системы и завершаем программу
        qDebug() << "\nSistema ne sovmestna tak kak rang[A] < rang[A|b]" << endl;
    else
    {
        ObratniHod();//иначе делаем обратный ход метода Гаусса
        //cout << "\nRezultat obratnogo hoda" << endl;
        //vivod_matrici(mtr, n, b, m);//выводим результат
        //printf("\nOtveti:\n");
        Vivod_Otvetov();//выводим полученные ответы
    }
    for (int i = 0; i < row; i++) {
        delete[]mtr[i];
    }
    delete[]mtr;
    delete[]b;
    //printf("\nNajmite 'y' dl9 povtornogo vvoda\n");

    ui->matrix_page->hide();
    ui->answer_page->show();

}


bool MainWindow::sravnenie(Complex &c)
{
    if (c.Re == 0 && c.Im == 0)
        return true;
    else
        return false;
}

bool MainWindow::sravnenie1(Complex &c)
{
    if ((-c.Re > 0 && -c.Im > 0) || (-c.Re == 0 && -c.Im > 0) || (-c.Re > 0 && -c.Im == 0))
        return true;
    else
        return false;
}

bool MainWindow::Swap(int i, int j)
{
    int z, w;
    class Complex r;
    for (z = i; z < row; z++)
    {
        if (!sravnenie(mtr[z][j]))
        {
            for (w = j; w < col; w++)
            {
                r = mtr[i][w];
                mtr[i][w] = mtr[z][w];
                mtr[z][w] = r;
            }
            r = b[i];
            b[i] = b[z];
            b[z] = r;
            return true;
        }
    }
    return false;
}

void MainWindow::vvod_matrici()
{
    int i, j;
    for (i = 0; i < col-1; i++)
    {
        for (j = 0; j < row; j++)
        {
            QTableWidgetItem *item = ui->tableWidget->item(i,j); //получим ячейку с индексами
            QString text = item->text(); //получим текст ячейки
            if(text.indexOf("+") != -1)
            {
                    QStringList list = text.split("+"); //разделим на две части по +
                    list[1].chop(1);//удалим i в конце
                    mtr[i][j].Re = list[0].toDouble();
                    mtr[i][j].Im = list[1].toDouble();
                    break;
            }
            else
            {
                mtr[i][j].Re = text.toDouble();
                mtr[i][j].Im = 0;
            }
        }
    }
    i = 0;
    for (int l = 0; l < col-1; l++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(i+l,j); //получим ячейку с индексами
        QString text = item->text(); //получим текст ячейки
        if(text.indexOf("+") != -1)
        {
                QStringList list = text.split("+"); //разделим на две части по +
                list[1].chop(1);//удалим i в конце
                b[l].Re = list[0].toDouble();
                b[l].Im = list[1].toDouble();
                break;
        }
        else
        {
            b[l].Re = text.toDouble();
            b[l].Im = 0;
        }
    }

}

int MainWindow::Ne_nol(int z)
{
    int j;
    for (j = 0; j < col; j++)
    {
        if (!sravnenie(mtr[z][j]))
        {
            return j;
        }
    }
    return -1;
}

/*void MainWindow::vivod_matrici()
{
    int i, j;
    cout.precision(3);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            cout << fixed << mtr[i][j] << ends;
        }
        cout << fixed << b[i] << endl;
    }
}*/

bool MainWindow::Rang()
{
    int j, i, rang1 = 0, rang2 = 0;
    for (j = 0; j < col; j++)
    {
        for (i = 0; i < row; i++)
        {
            if (!sravnenie(mtr[i][j]) && (i > rang1))
                rang1 = i;//наибольший индекс элемента матрицы коэффициентов в столбце
        }
    }
    for (i = 0; i < row; i++)
    {
        if (!sravnenie(b[i]))
        {
            rang2 = i;//наибольший индекс элемента в столбце свободных членов
        }
    }
    if (rang2 > rang1)
        return false;
    else
        return true;
}

void MainWindow::PryamoiHod()
{
    class Complex v;
    int j, i, z, w;
    for (j = 0; j < col; j++)
    {
        for (i = (j + 1); i < row; i++)
        {
            w = j;
        back:
            if (sravnenie(mtr[j][w]))//если выбранный элемент равен нулю, ищем строку с ненулевым элементом
            {
                if (Swap((i - 1), w))//если нашли такую строку выполняется вычитание одной строки из другой
                {
                    v = mtr[i][w] / mtr[j][w];//коэффициент, на который домножается вычитаемая строка
                    for (z = w; z < col; z++)
                    {
                        mtr[i][z] = mtr[i][z] - (mtr[j][z] * v);
                    }
                    b[i] = b[i] - b[j] * v;
                }
                else//если столбец выбранного элемента нулевой - переходим к элементу справа от выбранного
                {
                    w++;
                    goto back;
                }
            }
            else//если выбранный элемент не равен нулю, вычитание строки производится сразу
            {
                v = mtr[i][w] / mtr[j][w];
                for (z = j; z < col; z++)
                {
                    mtr[i][z] = mtr[i][z] - (mtr[j][z] * v);
                }
                b[i] = b[i] - (b[j] * v);
            }
        }
    }
}

void MainWindow::ObratniHod()
{
    int j, i, z, l;
    for (z = (row - 1); z > 0; z--)
    {
        l = Ne_nol(z);
        if (l != (-1))//если нашли ненулевой элемент, производится вычитание строки
        {
            for (i = (z - 1); i > -1; i--)
            {
                b[i] = b[i] - (b[z] * (mtr[i][l] / mtr[z][l]));
                for (j = (col - 1); j >= l; j--)
                {
                    mtr[i][j] = mtr[i][j] - (mtr[z][j] * (mtr[i][l] / mtr[z][l]));
                }
            }
        }
    }
    for (z = 0; z < row; z++)//деление строки на значение базисной неизвестной
    {
        l = Ne_nol(z);
        if (l != (-1))//если нашли строку с ненулевым элементом - производится деление
        {
            b[z] = b[z] / mtr[z][l];
            for (j = (col - 1); j >= l; j--)
            {
                mtr[z][j] = (mtr[z][j]) / (mtr[z][l]);
            }
        }
    }
}

void MainWindow::Vivod_Otvetov()
{
    QString res = "Ответ: \n ";
    int i, l;
    for (i = 0; i < row; i++)
    {
        l = Ne_nol(i);
        //if (l != (-1))
            //cout.precision(3);
            res.append("x[")
                    .append(QString::number(l+1))
                    .append("] =")
                    .append(QString::number(b[i].Re, 'f',2))
                    .append("+")
                    .append(QString::number(b[i].Im, 'f',2))
                    .append("i")
                    .append("\n");

        //qDebug() << "x[" << l + 1 << "] =" << fixed << b[i].Re << b[i].Im << endl;
    }
    //QString res = "Ответ: x1= , x2= "; //здесь будет твой ответ
    ui->result->setText(res);
}

/*void MainWindow::Vivod_Otvetov()
{
    int i, j, l;
    for (i = 0; i < n; i++)
    {
        l = Ne_nol(mtr, i, m);
        if (l != (-1))
        {
            cout << "x[" << l + 1 << "] =" << ends;
            cout.precision(3);
            cout << fixed << b[i]<< ends;
            for (j = (l + 1); j < m; j++)
            {
                    cout << "+" << fixed << mtr[i][j] << "*x[" << j + 1 << "]"<< ends;
            }
        }
        cout << "" << endl;
    }
}*/
