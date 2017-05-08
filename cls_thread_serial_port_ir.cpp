#include "cls_thread_serial_port_ir.h"

clsThreadSerialPortIR::clsThreadSerialPortIR()
{
    input_keyboard = new clsInputKeyboard();
    list_ArduinoCmd_KeyboardCmd << " FORWARD" << "Up"
                                << " REVERSE" << "Down"
                                << " RIGHT" << "Right"
                                << " LEFT" << "Left"
                                << " -OK-" << "Enter"
                                << " *" << "Space"
                                << " 2" << "PgUp"
                                << " 5" << "PgDn"
                                << " 4" << "Left"
                                << " 6" << "Right"
                                   ;
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
        connect(&serial, SIGNAL(readyRead()),this, SLOT(handleReadyRead()));
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
    qba_command.append(qba_message);
    //simulator keyboard
    if(qba_command.indexOf("\r\n") > -1)
    {
        qba_message = qba_command.left(qba_command.indexOf("\r\n"));
        if(qba_message == " REPEAT")
        {
            input_command(qba_old_command);
        }
        else
        {
            input_command(qba_message);
            qba_old_command = qba_message;
        }
        qba_command.clear();
        slot_send_to_qml(qba_message);

    }
    else {
        slot_send_to_qml(qba_message);

    }
    qDebug() << __func__ << qba_message << qba_command;

}

void clsThreadSerialPortIR::slot_set_command(QStringList list_commands)
{
    list_ArduinoCmd_KeyboardCmd.clear();
    for( int i = 0; i < list_commands.count() ; i += 2)
    {
        QString _cmd = list_commands[i];
        QString _key_press = list_commands[ i + 1 ];
        qDebug() << list_commands[i] << list_commands[ i + 1 ];
        if(_cmd != "" && _key_press != "")
        {
            list_ArduinoCmd_KeyboardCmd << _cmd <<_key_press;
        }
    }
}

void clsThreadSerialPortIR::input_command(QByteArray qba_message)
{
    for(int i = 0; i < list_ArduinoCmd_KeyboardCmd.count(); i+=2 )
    {
        if(qba_message == list_ArduinoCmd_KeyboardCmd[i])
        {
            input_keyboard->input_single_command(list_ArduinoCmd_KeyboardCmd[i + 1]);
        }
    }
    /*
    if(qba_message == " FORWARD")
    {
        input_keyboard->input_single_command("Up");
    }
    else if(qba_message == " REVERSE")
    {
        input_keyboard->input_single_command("Down");
    }
    else if(qba_message == " RIGHT")
    {
        input_keyboard->input_single_command("Right");
    }
    else if(qba_message == " LEFT")
    {
        input_keyboard->input_single_command("Left");
    }
    else if(qba_message == " -OK-")
    {
        input_keyboard->input_single_command("Enter");
    }
    else if(qba_message == " *")
    {
        input_keyboard->input_single_command("Space");
    }
    else if(qba_message == " 2")
    {
        input_keyboard->input_single_command("PgUp");
    }
    else if(qba_message == " 5")
    {
        input_keyboard->input_single_command("PgDn");
    }
*/
}
void clsThreadSerialPortIR::slot_send_to_qml(QString msg)
{
    emit signal_send_to_qml(msg);
}
