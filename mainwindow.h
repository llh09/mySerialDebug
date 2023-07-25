#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSerialPort *serialPort;
private slots:
    void on_openBtn_clicked();

    void on_closeBtn_clicked();

    void serialPortReadyRead_Slot();

    void on_sendBtn_clicked();

    void on_clearBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
