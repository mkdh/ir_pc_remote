#include "cls_thread_serial_port_ir.h"

clsThreadSerialPortIR::clsThreadSerialPortIR()
{
    input_keyboard = new clsInputKeyboard();
}

clsThreadSerialPortIR::~clsThreadSerialPortIR()
{
    msleep(3000);
    this->thread()->quit();
    this->thread()->wait(3000);
#if __APPLE__
    this->terminate();
#else
#endif
}

bool clsThreadSerialPortIR::slot_open_serial_port()
{
    serial.setPortName("COM5");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    //http://stackoverflow.com/questions/28770862/qserialport-proper-sending-of-many-lines
    serial.setFlowControl(QSerialPort::SoftwareControl);//serial.setFlowControl(QSerialPort::NoFlowControl);

    if(!serial.isOpen())
    {
        serial.open(QIODevice::ReadWrite);
    }

    if(serial.isOpen())
    {
        //this->start();
        //http://stackoverflow.com/questions/26612852/how-does-readyread-work-in-qt
        connect(&serial, SIGNAL(readyRead()), SLOT(handleReadyRead()));
        slot_send_to_qml("serial.isOpen(): true");
        return true;
    }
    else
    {
        slot_send_to_qml("serial.isOpen(): false");

        return false;
    }
}

void clsThreadSerialPortIR::handleReadyRead()
{
    QByteArray qba_message;
    qba_message = serial.readAll();
    qDebug() << __func__ << qba_message;

    slot_send_to_qml(qba_message);
    //simulator keyboard
    if(qba_message == "Up")
    {
        input_keyboard->input_single_command("Up");
    }
}

void clsThreadSerialPortIR::slot_send_to_qml(QString msg)
{
    emit signal_send_to_qml(msg);
}
