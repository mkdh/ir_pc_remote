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

bool clsThreadSerialPortIR::open_serial_port()
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
        return true;
    }
    else
    {
        return false;
    }
}

void clsThreadSerialPortIR::handleReadyRead()
{
    qDebug() __func__ << serial.readAll();
    slot_send_to_qml(serial);
}

void clsThreadSerialPortIR::slot_send_to_qml(QString msg)
{
    emit signal_send_to_qml(msg);
}
