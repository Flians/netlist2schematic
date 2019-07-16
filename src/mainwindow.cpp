#include "include/mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->input_verilog, SIGNAL(returnPressed()), this, SLOT(input_verilog()));
    connect(ui->input_skin, SIGNAL(returnPressed()), this, SLOT(input_skin()));
    connect(ui->button_prase, SIGNAL(clicked(bool)), this, SLOT(parse_verilog()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input_verilog()
{
    QString verilog_files = QFileDialog::getOpenFileName(
                this, "Select verilog files:",
                QCoreApplication::applicationDirPath(),
                "Verilog (*.v);; All files (*.*);; ");
    ui->input_verilog->setText(verilog_files);
    qDebug() << "path=" << verilog_files;
}

void MainWindow::input_skin()
{
    QString skin_file = QFileDialog::getOpenFileName(
                this, "Select delay files:",
                QCoreApplication::applicationDirPath(),
                "skin (*.svg);; All files (*.*);; ");
    ui->input_skin->setText(skin_file);
    qDebug() << "path=" << skin_file;
}

void MainWindow::parse_verilog()
{
    try {
        // Initialize Circuit
        Graph circuit;
        circuit.parse_verilog(ui->input_verilog->text().toStdString());
        circuit.parse_skin(ui->input_skin->text().toStdString());
    }
    catch (ParseError& e) {
        ui->text_prase_putout->append("ParseError: " + QString::fromStdString(e.what()));
    }
    catch (exception& e) {
        ui->text_prase_putout->append(QString::fromStdString(e.what()));
    }
}
