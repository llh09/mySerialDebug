#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList serialNamePort;

    serialPort = new QSerialPort(this);

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(serialPortReadyRead_Slot()));

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        serialNamePort<<info.portName();
    }

    ui->comboBox->addItems(serialNamePort);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::serialPortReadyRead_Slot()
{
    QString buf;
    buf = QString(serialPort->readAll());
    ui->recvEdit->appendPlainText(buf);
}

void MainWindow::on_openBtn_clicked()
{
    QSerialPort::BaudRate baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::StopBits stopBits;
    QSerialPort::Parity checkBits;

    if(ui->baudRateCB->currentText() == "4800")
    {
        baudRate = QSerialPort::Baud4800;
    }
    else if(ui->baudRateCB->currentText() == "9600")
    {
        baudRate = QSerialPort::Baud4800;
    }
    else if(ui->baudRateCB->currentText() == "38400")
    {
        baudRate = QSerialPort::Baud38400;
    }
    else if(ui->baudRateCB->currentText() == "57600")
    {
        baudRate = QSerialPort::Baud57600;
    }
    else if(ui->baudRateCB->currentText() == "115200")
    {
        baudRate = QSerialPort::Baud115200;
    }

    if(ui->dataLenCB->currentText() == "5")
    {
        dataBits = QSerialPort::Data5;
    }
    else if(ui->dataLenCB->currentText() == "6")
    {
        dataBits = QSerialPort::Data6;
    }
    else if(ui->dataLenCB->currentText() == "7")
    {
        dataBits = QSerialPort::Data7;
    }
    else if(ui->dataLenCB->currentText() == "8")
    {
        dataBits = QSerialPort::Data8;
    }

    if(ui->stopBitCB->currentText() == "1")
    {
        stopBits = QSerialPort::OneStop;
    }
    else if(ui->stopBitCB->currentText() == "1.5")
    {
        stopBits = QSerialPort::OneAndHalfStop;
    }
    else if(ui->stopBitCB->currentText() == "2")
    {
        stopBits = QSerialPort::TwoStop;
    }

    if(ui->chechBitCB->currentText() == "无")
    {
        checkBits = QSerialPort::NoParity;
    }
    if(ui->chechBitCB->currentText() == "奇校验")
    {
        checkBits = QSerialPort::OddParity;
    }
    if(ui->chechBitCB->currentText() == "偶校验")
    {
        checkBits = QSerialPort::EvenParity;
    }

    serialPort->setPortName(ui->comboBox->currentText());
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(dataBits);
    serialPort->setStopBits(stopBits);
    serialPort->setParity(checkBits);

    if(serialPort->open(QIODevice::ReadWrite) == true)
    {
        QMessageBox::information(this, "提示", "成功");
    }
    else
    {
        QMessageBox::critical(this, "提示", "失败");
    }
}

void MainWindow::on_closeBtn_clicked()
{
    serialPort->close();
}

void MainWindow::on_sendBtn_clicked()
{
    serialPort->write(ui->plainTextEdit_2->toPlainText().toLocal8Bit().data());
}

void MainWindow::on_clearBtn_clicked()
{
    ui->recvEdit->clear();
}
