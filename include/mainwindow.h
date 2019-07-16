#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QDir>

#include <iostream>
#include "include/graph/graph.h"
#include "include/error/parse_error.h"

using namespace std;
using namespace ns;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void input_verilog();
    void input_skin();
    void parse_verilog();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
