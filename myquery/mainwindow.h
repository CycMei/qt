#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "connection.h"

#include <QMainWindow>
#include <QPushButton>
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
