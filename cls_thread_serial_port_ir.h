#ifndef CLS_THREAD_SERIAL_PORT_IR_H
#define CLS_THREAD_SERIAL_PORT_IR_H

#include <QThread>
#include <QtSerialPort/QSerialPort>
#include "cls_input_keyboard.h"
#include <QDebug>
class clsThreadSerialPortIR: public QThread
{
    Q_OBJECT
public:
    clsThreadSerialPortIR();
    ~clsThreadSerialPortIR();
private:
    QSerialPort serial;
    clsInputKeyboard* input_keyboard;

    void handleReadyRead();
public slots:
    void slot_send_to_qml(QString msg);
    bool slot_open_serial_port();
signals:
    void signal_send_to_qml(QString msg);


};

#endif // CLS_THREAD_SERIAL_PORT_IR_H
