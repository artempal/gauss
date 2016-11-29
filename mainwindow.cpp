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
    ui->tableWidget->setColumnCount(col); // указываем количество столбцов
    ui->tableWidget->setHorizontalHeaderLabels(head); //задаем шапку

    // выделяем память под все ячейки таблицы
    for(int stroka = 0; stroka <  row; stroka++)
      for(int stolbeu = 0; stolbeu <  col; stolbeu++)
            ui->tableWidget->setItem(stroka, stolbeu, new QTableWidgetItem());


    // выделяем память под все ячейки таблицы
    for(int stroka = 0; stroka < row; stroka++)
      for(int stolbeu = 0; stolbeu < col; stolbeu++)
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
    ui->matrix_page->hide();
    ui->answer_page->show();


    //не забудь сделать очистку памяти для Im и Re, а то у меня мозг уже не работает
}
