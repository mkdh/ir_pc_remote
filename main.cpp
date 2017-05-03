#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "cls_thread_serial_port_ir.h"
clsThreadSerialPortIR* g_cls_thread_serial_port_ir = 0;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QQmlContext *ctext = engine.rootContext();

    //new serial port
    g_cls_thread_serial_port_ir = new clsThreadSerialPortIR;
    ctext->setContextProperty("g_cls_thread_serial_port_ir", g_cls_thread_serial_port_ir);

    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
