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
    QByteArray qba_command;
    QByteArray qba_old_command;
    void input_command(QByteArray qba_message);
    QStringList list_ArduinoCmd_KeyboardCmd;
public slots:
    void slot_send_to_qml(QString msg);
    bool slot_open_serial_port();
    void handleReadyRead();
    void slot_set_command(QStringList list_commands);
signals:
    void signal_send_to_qml(QString msg);


};

#endif // CLS_THREAD_SERIAL_PORT_IR_H
